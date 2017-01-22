#include <VMModule.hpp>

VMModule::VMModule(void):
	AMonitorModule("Virtual Memory (in Mb)")
{
	this->updateModule();
}

VMModule::~VMModule(void)
{}

void
VMModule::updateModule(void)
{
	struct xsw_usage	vm_usage;

	use_sysctl("vm.swapusage", vm_usage);
	this->_numbers["Total size"] = vm_usage.xsu_total / (1024 * 1024);
	this->_numbers["Available"] = vm_usage.xsu_avail / (1024 * 1024);
	this->_numbers["Used"] = vm_usage.xsu_used / (1024 * 1024);
}
