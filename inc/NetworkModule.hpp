#ifndef NETWORKMODULE_HPP

# define NETWORKMODULE_HPP

# include <AMonitorModule.hpp>

# include <sys/sysctl.h>
# include <net/if.h>
# include <net/route.h>

struct s_network_data
{
	long double		ibytes;
	long double		obytes;
	long double		ipackets;
	long double		opackets;
};

class NetworkModule: public AMonitorModule
{
	public:
		NetworkModule(void);
		virtual ~NetworkModule(void);

		virtual void		updateModule(void);

	private:
		NetworkModule(NetworkModule const&);

		NetworkModule&		operator=(NetworkModule const&);
		template<typename T>
		void				_get_network_state(s_network_data &network_data, int wanted_list, unsigned char info);
		void				_init(void);

		s_network_data		_save;
};

#endif
