#include <CPUModule.hpp>
#include <cmath>
#include <mach/vm_statistics.h>
#include <mach/mach_types.h>
#include <mach/mach_init.h>
#include <mach/mach_host.h>

CPUModule::CPUModule(void):
	AMonitorModule("CPU")
{
	this->_init();
}

CPUModule::~CPUModule()
{}

void
CPUModule::_init(void)
{
	int32_t		activecpu;
	int64_t		cpufrequency;
	char		model[1024];

	use_sysctl("hw.activecpu", activecpu);
	this->_strings["Active of active core"] = number_to_string(activecpu);

	use_sysctl("hw.cpufrequency", cpufrequency);
	this->_strings["Frequency (in Ghz)"] = number_to_string(cpufrequency / pow(10, 9));

	use_sysctl("machdep.cpu.brand_string", model, 1024);
	this->_strings["Model"] = std::string(model);

	this->updateModule();
}

void
CPUModule::_get_CPU_load(void)
{
	kern_return_t kr;
	mach_msg_type_number_t count;
	host_cpu_load_info_data_t r_load;

	uint64_t totalSystemTime = 0, totalUserTime = 0, totalIdleTime = 0, total = 0;
	long double percent;

	count = HOST_CPU_LOAD_INFO_COUNT;
	kr = host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (int *)&r_load, &count);
	if (kr != KERN_SUCCESS) {
		perror("Kernel error");
		exit(0);
	}

	totalSystemTime = r_load.cpu_ticks[CPU_STATE_SYSTEM];
	totalUserTime = r_load.cpu_ticks[CPU_STATE_USER] + r_load.cpu_ticks[CPU_STATE_NICE];
	totalIdleTime = r_load.cpu_ticks[CPU_STATE_IDLE];
	total = totalSystemTime + totalUserTime + totalIdleTime;
	percent = static_cast<long double>(total) / 100.;

	this->_numbers["System usage (in %)"] = static_cast<long double>(totalSystemTime) / percent;
	this->_numbers["User usage (in %)"] = static_cast<long double>(totalUserTime) / percent;
	this->_numbers["Idle usage (in %)"] = static_cast<long double>(totalIdleTime) / percent;
}

void
CPUModule::updateModule(void)
{
	this->_get_CPU_load();
}
