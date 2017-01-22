#include <NCurses.hpp>

NCurses::NCurses(std::vector<IMonitorModule*>& modules):
	_modules(modules)
{
	struct winsize		winsize;

	ioctl(1, TIOCGWINSZ, &winsize);
	this->_max_x = winsize.ws_col;
	this->_max_y = winsize.ws_row;
	this->_win = newwin(winsize.ws_row, winsize.ws_col, 0, 0);
	initscr();
	noecho();
	curs_set(0);
	start_color();
	cbreak();
	init_color(COLOR_CYAN, 212, 212, 212);
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
}

NCurses::~NCurses(void)
{
	endwin();
}

void
NCurses::refreshMonitor(void)
{
	wclear(this->_win);

	for (
			std::vector<IMonitorModule*>::iterator it = this->_modules.begin();
			it != this->_modules.end();
			it++
		)
	{
		IMonitorModule		*module = *it;

		this->_drawName(module->getName());
		this->_print("\n");
		this->_drawStrings(module->getStrings());
		this->_print("\n");
		this->_drawNumbers(module->getNumbers());
		this->_print("\n");
	}

	wrefresh(this->_win);
}

void
NCurses::_print(const char *str)
{
	if (this->_y < this->_max_y)
	{
		mvwprintw(this->_win, this->_y, 0, str);
		mvwprintw(this->_win, this->_y, strlen(str), "\n");
		this->_y++;
	}
}

void
NCurses::_drawName(std::string const &name)
{
	size_t			title_size = 36;
	size_t			title_position = (title_size - name.size()) / 2;
	std::string		title_border('*', title_size);
	std::string		title(' ', title_size);

	title[0] = '*';
	title[title_size - 1] = '*';
	title.replace(title_position, name.size(), name);
	this->_print(title_border.c_str());
	this->_print(title.c_str());
	this->_print(title_border.c_str());
}

void
NCurses::_drawStrings(std::map<std::string, std::string> const &strings)
{
	for (
			std::map<std::string, std::string>::const_iterator it = strings.begin();
			it != strings.end();
			it++
		)
	{
		std::stringstream		ss;

		ss << it->first << ": " << it->second;
		this->_print(ss.str().c_str());
	}
}

void
NCurses::_drawNumbers(std::map<std::string, long double> const &numbers)
{
	for (
			std::map<std::string, long double>::const_iterator it = numbers.begin();
			it != numbers.end();
			it++
		)
	{
		std::stringstream		ss;

		ss << it->first << ": " << it->second;
		this->_print(ss.str().c_str());
	}
}
