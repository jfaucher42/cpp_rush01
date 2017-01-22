#ifndef OSMODULE_HPP

# define OSMODULE_HPP

# include <AMonitorModule.hpp>
# include <sstream>

# include <sys/utsname.h>

class OSModule: public AMonitorModule
{
	public:
		OSModule(void);
		virtual ~OSModule(void);

		virtual void	updateModule(void);

	private:
		OSModule(OSModule const&);
		OSModule&		operator=(OSModule const&);

		void			_init(void);
};

#endif
