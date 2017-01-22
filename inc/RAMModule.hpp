#ifndef RAMMODULE_HPP

# define RAMMODULE_HPP

# include <AMonitorModule.hpp>
# include <utils.hpp>

# include <mach/vm_statistics.h>
# include <mach/mach_types.h>
# include <mach/mach_init.h>
# include <mach/mach_host.h>

class RAMModule: public AMonitorModule
{
	public:
		RAMModule(void);
		virtual ~RAMModule(void);

		virtual void	updateModule(void);

	private:
		RAMModule(RAMModule const&);
		RAMModule&		operator=(RAMModule const&);
};

#endif
