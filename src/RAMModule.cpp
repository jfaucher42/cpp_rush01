#include <RAMModule.hpp>

RAMModule::RAMModule(void):
	AMonitorModule("RAM state (in Mb)")
{
	this->updateModule();
}

RAMModule::~RAMModule(void)
{}

static int64_t
get_used_RAM()
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

void
RAMModule::updateModule(void)
{
	int64_t				ram_size;
	int64_t				used_ram;

	used_ram = get_used_RAM();
	use_sysctl("hw.memsize", ram_size);
	this->_numbers["Total size"] = ram_size / (1024 * 1024);
	this->_numbers["Available"] = (ram_size - used_ram) / (1024 * 1024);
	this->_numbers["Used"] = used_ram / (1024 * 1024);
}
