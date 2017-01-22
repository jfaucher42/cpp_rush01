#ifndef AMONITORMODULE_HPP

# define AMONITORMODULE_HPP

# include <IMonitorModule.hpp>

class AMonitorModule: public IMonitorModule
{
	public:
		AMonitorModule(std::string);
		virtual ~AMonitorModule(void);

		virtual std::string const							getName(void) const;
		virtual std::map<std::string, std::string> const	getStrings(void) const;
		virtual std::map<std::string, long double> const	getNumbers(void) const;

	protected:
		std::string								_name;
		std::map<std::string, std::string>		_strings;
		std::map<std::string, long double>		_numbers;

	private:
		AMonitorModule(void);
		AMonitorModule(AMonitorModule const&);
		AMonitorModule&		operator=(AMonitorModule const&);
};

#endif
