#ifndef CPUMODULE_HPP

# define CPUMODULE_HPP

# include <sstream>
# include <utils.hpp>
# include <IMonitorModule.hpp>

class CPUModule: public IMonitorModule
{
	public:
		CPUModule(void);
		virtual ~CPUModule();

		virtual std::string const							getName(void) const;
		virtual std::map<std::string, std::string> const	getStrings(void) const;
		virtual std::map<std::string, long double> const	getNumbers(void) const;
		virtual void										updateModule(void);

	private:
		CPUModule(CPUModule const&);
		CPUModule&		operator=(CPUModule const&);

		void			_init(void);
		void			_get_CPU_load(void);

		std::string								_name;
		std::map<std::string, std::string>		_strings;
		std::map<std::string, long double>		_numbers;
};

#endif
