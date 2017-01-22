#ifndef IMONITORMODULE_HPP

# define IMONITORMODULE_HPP

# include <map>
# include <string>

class IMonitorModule
{
	public:
		virtual ~IMonitorModule() {}

		virtual std::string const							getName(void) const = 0;
		virtual std::map<std::string, std::string> const	getStrings(void) const = 0;
		virtual std::map<std::string, long double> const	getNumbers(void) const = 0;
		virtual void										updateModule(void) = 0;
};

#endif
