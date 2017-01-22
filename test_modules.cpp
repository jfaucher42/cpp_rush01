#include <iostream>
#include <cmath>

/* <<< PART 1 */
#include <unistd.h>

void	host_info(void)
{
	char	buff[BUFSIZ];
	getlogin_r(buff, BUFSIZ);
	size_t		len = strlen(buff);
	buff[len++] = '@';
	gethostname(buff + len, BUFSIZ - len);
	printf("%s\n", buff);
}

#include <sys/utsname.h>

void	machine_info(void)
{
	struct utsname unameData;

	uname(&unameData);

	printf("%s\n", unameData.sysname);
	printf("%s\n", unameData.nodename);
	printf("%s\n", unameData.release);
	printf("%s\n", unameData.version);
	printf("%s\n", unameData.machine);
	/*
Darwin
e3r1p1.42.fr
16.1.0
Darwin Kernel Version 16.1.0: Wed Oct 19 20:31:56 PDT 2016; root:xnu-3789.21.4~4/RELEASE_X86_64
x86_64
	 */
}

#include <ctime>

void	date(void)
{
	std::time_t result = std::time(nullptr);

	std::string		time = std::asctime(std::localtime(&result));
	time.pop_back();
	std::cout << time << std::endl;;
}

void	part1(void)
{
	host_info();
	machine_info();
	date();
}
/* >>> */

/* <<< PART 2 */

#include <sys/sysctl.h>
#include <unistd.h>

template<typename T>
void	use_sysctl(const char *name, T& data, size_t fixed = 0)
{
	size_t		size;

	if (fixed)
		size = fixed;
	else
		size = sizeof(T);
	sysctlbyname(name, &data, &size, NULL, 0);
}

#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

long long		get_used_RAM()
{
	vm_size_t page_size;
	mach_port_t mach_port;
	mach_msg_type_number_t count;
	vm_statistics64_data_t vm_stats;

	mach_port = mach_host_self();
	count = sizeof(vm_stats) / sizeof(natural_t);
	if (KERN_SUCCESS == host_page_size(mach_port, &page_size) &&
		KERN_SUCCESS == host_statistics64(mach_port, HOST_VM_INFO,
										(host_info64_t)&vm_stats, &count))
		return ((int64_t)vm_stats.active_count +
			   (int64_t)vm_stats.inactive_count +
			   (int64_t)vm_stats.wire_count) *  (int64_t)page_size;
	return -1;
}

typedef struct		s_cpu_usage
{
	uint64_t		total_system_time;
	uint64_t		total_user_time;
	uint64_t		total_idle_time;
}					t_cpu_usage;

void	get_CPU_load(t_cpu_usage &cpu_usage)
{
	kern_return_t kr;
	mach_msg_type_number_t count;
	host_cpu_load_info_data_t r_load;

	uint64_t totalSystemTime = 0, totalUserTime = 0, totalIdleTime = 0;

	count = HOST_CPU_LOAD_INFO_COUNT;
	kr = host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (int *)&r_load, &count);
	if (kr != KERN_SUCCESS) {
		printf("Kernel error\n");
		return;
	}

	cpu_usage.total_system_time = r_load.cpu_ticks[CPU_STATE_SYSTEM];
	cpu_usage.total_user_time = r_load.cpu_ticks[CPU_STATE_USER] + r_load.cpu_ticks[CPU_STATE_NICE];
	cpu_usage.total_idle_time = r_load.cpu_ticks[CPU_STATE_IDLE];
}

void	part2()
{
	int32_t				activecpu;
	int64_t				cpufrequency;
	int64_t				ram_size;
	int64_t				used_ram;
	struct clockinfo	clockinfo;
	struct xsw_usage	vm_usage;
	char				model[1024];
	t_cpu_usage			cpu_usage;

	use_sysctl("hw.activecpu", activecpu);
	std::cout << "Active cpu: " << activecpu << std::endl;

	use_sysctl("hw.cpufrequency", cpufrequency);
	std::cout << "CPU frequency: " << cpufrequency / pow(10, 9) << " hz" << std::endl;

	use_sysctl("machdep.cpu.brand_string", model, 1024);
	std::cout << "CPU model: " << model << std::endl;

	use_sysctl("vm.swapusage", vm_usage);
	std::cout << std::hex << std::showbase
			  << "Virtual memory usage (in Mb):" << std::endl
			  << "Total: " << vm_usage.xsu_total / (1024 * 1024) << std::endl
			  << "Available: " << vm_usage.xsu_avail / (1024 * 1024) << std::endl
			  << "Used: " << vm_usage.xsu_used / (1024 * 1024) << std::endl
			  << std::dec;

	use_sysctl("hw.memsize", ram_size);
	used_ram = get_used_RAM();

	std::cout << std::hex << std::showbase
			  << "RAM usage (in Mb):" << std::endl
			  << "Total: " << ram_size / (1024 * 1024) << std::endl
			  << "Available: " << (ram_size - used_ram) / (1024 * 1024) << std::endl
			  << "Used: " << used_ram / (1024 * 1024) << std::endl
			  << std::dec;

	get_CPU_load(cpu_usage);

	uint64_t total = cpu_usage.total_system_time + cpu_usage.total_user_time + cpu_usage.total_idle_time;

	double one_percent = static_cast<double>(total) / 100.0;

	std::cout << "Total: " << total << std::endl;
	std::cout << "One percent: " << one_percent << std::endl;

	std::cout << "CPU usage:" << std::endl
			  << "System: " << static_cast<double>(cpu_usage.total_system_time) / one_percent << "%" << std::endl
			  << "User: " << static_cast<double>(cpu_usage.total_user_time) / one_percent << "%" << std::endl
			  << "Idle: " << static_cast<double>(cpu_usage.total_idle_time) / one_percent << "%" << std::endl;

}

/* >>> */

/* <<< PART 3 */

#include <sys/sysctl.h>
#include <net/if.h>
#include <net/route.h>
#include <cstring>

typedef struct		s_network_data
{
	long double		ibytes;
	long double		obytes;
	long double		ipackets;
	long double		opackets;
}					t_network_data;

template<typename T>
void	network(t_network_data &network_data, int wanted_list, unsigned char info)
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
			//network_data.ipackets += static_cast<long double>(msghdr->ifm_data.ifi_imcasts);
			network_data.opackets += static_cast<long double>(msghdr->ifm_data.ifi_opackets);
			//network_data.opackets += static_cast<long double>(msghdr->ifm_data.ifi_omcasts);
		}

	}
	delete[] data;
}

void	part3(t_network_data &saved)
{
	t_network_data		network_data = {0, 0, 0, 0};

	network<struct if_msghdr>(network_data, NET_RT_IFLIST, RTM_IFINFO);
	network<struct if_msghdr2>(network_data, NET_RT_IFLIST2, RTM_IFINFO2);

	std::cout << std::hex
			  << "# of received Kb per s: " << (network_data.ibytes - saved.ibytes) / 1024 << std::endl
			  << "# of sent Kb per s: " << (network_data.obytes - saved.obytes) / 1024 << std::endl
			  << "# of received packets per s: " << network_data.ipackets - saved.ipackets << std::endl
			  << "# of sent packets per s: " << network_data.opackets - saved.opackets << std::endl;
	std::cout << std::endl;

	saved = network_data;

}

/* >>> */

int		main()
{
	t_network_data		saved = {0, 0, 0, 0};

	network<struct if_msghdr>(saved, NET_RT_IFLIST, RTM_IFINFO);
	network<struct if_msghdr2>(saved, NET_RT_IFLIST2, RTM_IFINFO2);
	sleep(1);

	while (true)
	{
		std::cout << "PART 1: general user / computer information" << std::endl;
		part1();

		std::cout << std::endl;

		std::cout << "PART 2: CPU / RAM information" << std::endl;
		part2();

		std::cout << std::endl;

		std::cout << "PART 3: Network exchanges" << std::endl;
		part3(saved);
		sleep(1);
	}
}

// vim: set fdm=marker fmr=<<<,>>> fdl=0
