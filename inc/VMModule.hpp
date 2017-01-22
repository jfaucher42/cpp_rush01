#ifndef VMMODULE_HPP

# define VMMODULE_HPP

# include <AMonitorModule.hpp>
# include <utils.hpp>

class VMModule: public AMonitorModule
{
	public:
		VMModule(void);
		virtual ~VMModule(void);

		virtual void	updateModule(void);

	private:
		VMModule(VMModule const&);
		VMModule&		operator=(VMModule const&);
};

#endif
