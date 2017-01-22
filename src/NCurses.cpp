#include <NCurses.hpp>

const size_t	NCurses::_titleSize = 80;

NCurses::NCurses(std::vector<IMonitorModule*>& modules):
	_modules(modules)
{
	initscr();
	noecho();
	curs_set(0);
	start_color();
	cbreak();
	init_color(COLOR_CYAN, 212, 212, 212);
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);

	signal(SIGWINCH, &exit);

	struct winsize		winsize;

	if (ioctl(1, TIOCGWINSZ, &winsize) == -1)
	{
		perror("ioctl");
		exit(0);
	}
	this->_max_x = winsize.ws_col;
	this->_max_y = winsize.ws_row;
	this->_win = newwin(0, 0, 0, 0);
	if (!this->_win)
	{
		perror("newwin");
		exit(0);
	}
	nodelay(this->_win, true);
	napms(50);
}

NCurses::~NCurses(void)
{
	delwin(this->_win);
	endwin();
}

void
NCurses::launch(void)
{
	time_t		old_time, actual_time;

	std::time(&old_time);
	while (true)
	{
		werase(this->_win);
		this->_y = 0;

		for (
				std::vector<IMonitorModule*>::iterator it = this->_modules.begin();
				it != this->_modules.end();
				it++
			)
		{
			IMonitorModule		*module = *it;

			wattron(this->_win, COLOR_PAIR(1));
			this->_drawName(module->getName());
			wattron(this->_win, COLOR_PAIR(1));
			this->_drawMap(module->getStrings());
			this->_drawMap(module->getNumbers());
			this->_print("");
		}

		wrefresh(this->_win);

		if (wgetch(this->_win) == 27)
			break ;

		std::time(&actual_time);
		if (actual_time != old_time)
		{
			this->_updateModules();
			old_time = actual_time;
		}
	}
}

void
NCurses::_print(const char *str)
{
	if (this->_y < this->_max_y)
	{
		wprintw(this->_win, "%s\n", str);
		this->_y++;
	}
}

void
NCurses::_drawName(std::string const &name)
{
	size_t			title_position = (NCurses::_titleSize - name.size()) / 2;
	std::string		title_border;
	std::string		title;

	title_border.resize(NCurses::_titleSize, '*');
	title.resize(NCurses::_titleSize, ' ');
	title.replace(title_position, name.size(), name);
	title.resize(NCurses::_titleSize, ' ');
	title[0] = '*';
	title[NCurses::_titleSize - 1] = '*';
	this->_print(title_border.c_str());
	this->_print(title.c_str());
	this->_print(title_border.c_str());
}

template<typename T>
void
NCurses::_drawMap(T const &map)
{
	for (
			typename T::const_iterator it = map.begin();
			it != map.end();
			it++
		)
	{
		std::stringstream		ss;

		ss << it->first << ": ";

		wattron(this->_win, COLOR_PAIR(2));
		wprintw(this->_win, "%s", ss.str().c_str());
		wattron(this->_win, COLOR_PAIR(2));

		ss.str("");
		ss.clear();
		ss << it->second;

		wattron(this->_win, COLOR_PAIR(3));
		wprintw(this->_win, "%s\n", ss.str().c_str());
		wattron(this->_win, COLOR_PAIR(3));
	}
}

void
NCurses::_updateModules(void)
{
	for (
			std::vector<IMonitorModule*>::const_iterator it = this->_modules.begin();
			it != this->_modules.end();
			it++
		)
		reinterpret_cast<IMonitorModule*>(*it)->updateModule();
}
