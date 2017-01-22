#ifndef CPUMODULE_HPP

# define CPUMODULE_HPP

# include <sstream>
# include <utils.hpp>
# include <AMonitorModule.hpp>

class CPUModule: public AMonitorModule
{
	public:
		CPUModule(void);
		virtual ~CPUModule();

		virtual void										updateModule(void);

	private:
		CPUModule(CPUModule const&);
		CPUModule&		operator=(CPUModule const&);

		void			_init(void);
		void			_get_CPU_load(void);
};

#endif
