#include <NetworkModule.hpp>

NetworkModule::NetworkModule(void):
	AMonitorModule("Network")
{
	this->_init();
}

NetworkModule::~NetworkModule(void)
{}

template<typename T>
void
NetworkModule::_get_network_state(s_network_data &network_data, int wanted_list, unsigned char info)
{
	size_t			len;
	T				*msghdr;
	int				name[6] = {
		CTL_NET,
		PF_ROUTE,
		0,
		0,
		wanted_list,
		0
	};

	sysctl(name, 6, NULL, &len, NULL, 0);
	char	*data = new char[len];
	sysctl(name, 6, data, &len, NULL, 0);

	for (char *next = data; next < data + len; next += msghdr->ifm_msglen)
	{
		msghdr = reinterpret_cast<T*>(next);

		if (msghdr->ifm_type == info)
		{
			network_data.ibytes += static_cast<long double>(msghdr->ifm_data.ifi_ibytes);
			network_data.obytes += static_cast<long double>(msghdr->ifm_data.ifi_obytes);
			network_data.ipackets += static_cast<long double>(msghdr->ifm_data.ifi_ipackets);
			network_data.opackets += static_cast<long double>(msghdr->ifm_data.ifi_opackets);
		}

	}
	delete[] data;
}

void
NetworkModule::updateModule(void)
{
	s_network_data		new_data;

	new_data.ibytes = 0;
	new_data.obytes = 0;
	new_data.ipackets = 0;
	new_data.opackets = 0;
	this->_get_network_state<struct if_msghdr>(new_data, NET_RT_IFLIST, RTM_IFINFO);
	this->_get_network_state<struct if_msghdr2>(new_data, NET_RT_IFLIST2, RTM_IFINFO2);

	this->_numbers["# of received Kb per s"] = (new_data.ibytes - this->_save.ibytes) / 1024;
	this->_numbers["# of sent Kb per s"] = (new_data.obytes - this->_save.obytes) / 1024;
	this->_numbers["# of received packets per s"] = new_data.ipackets - this->_save.ipackets;
	this->_numbers["# of sent packets per s"] = new_data.opackets - this->_save.opackets;

	this->_save.ibytes = new_data.ibytes;
	this->_save.obytes = new_data.obytes;
	this->_save.ipackets = new_data.ipackets;
	this->_save.opackets = new_data.opackets;
}

void
NetworkModule::_init(void)
{
	this->_save.ibytes = 0;
	this->_save.obytes = 0;
	this->_save.ipackets = 0;
	this->_save.opackets = 0;
	this->_get_network_state<struct if_msghdr>(this->_save, NET_RT_IFLIST, RTM_IFINFO);
	this->_get_network_state<struct if_msghdr2>(this->_save, NET_RT_IFLIST2, RTM_IFINFO2);
	this->_numbers["# of received Kb per s"] = 0;
	this->_numbers["# of sent Kb per s"] = 0;
	this->_numbers["# of received packets per s"] = 0;
	this->_numbers["# of sent packets per s"] = 0;
}
