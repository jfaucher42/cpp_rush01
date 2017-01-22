#ifndef USERMODULE_HPP

# define USERMODULE_HPP

# include <AMonitorModule.hpp>

# include <unistd.h>

class UserModule: public AMonitorModule
{
	public:
		UserModule(void);
		virtual ~UserModule(void);

		virtual void	updateModule(void);

	private:
		UserModule(UserModule const&);
		UserModule&		operator=(UserModule const&);

		void			_init(void);
};

#endif
