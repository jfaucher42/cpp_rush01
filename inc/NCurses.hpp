#ifndef NCURSES_HPP

# define NCURSES_HPP

# include <ctime>
# include <vector>
# include <map>
# include <fstream>
# include <sstream>
# include <IMonitorDisplay.hpp>
# include <ncurses.h>
# include <sys/ioctl.h>
# include <cstdio>

class NCurses: public IMonitorDisplay
{
	public:
		NCurses(std::vector<IMonitorModule*>&);
		virtual ~NCurses(void);

		virtual void						launch(void);

	private:
		NCurses(void);
		NCurses(NCurses const&);

		NCurses&							operator=(NCurses const&);
		void								_print(const char*);
		void								_drawName(std::string const&);
		void								_drawStrings(std::map<std::string, std::string> const&);
		void								_drawNumbers(std::map<std::string, long double> const&);
		void								_updateModules(void);

		std::ofstream						_out;
		WINDOW*								_win;
		std::vector<IMonitorModule*>&		_modules;
		size_t								_x;
		size_t								_y;
		size_t								_max_x;
		size_t								_max_y;
};

#endif
