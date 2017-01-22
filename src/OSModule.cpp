#include <OSModule.hpp>

static std::string
getOsName(void)
{
#ifdef _WIN32
	return "Windows 32-bit";
#elif _WIN64
	return "Windows 64-bit";
#elif __unix || __unix__
	return "Unix";
#elif __APPLE__ || __MACH__
	return "Mac OSX";
#elif __linux__
	return "Linux";
#elif __FreeBSD__
	return "FreeBSD";
#else
	return "Other";
#endif
}

OSModule::OSModule(void):
	AMonitorModule("OS information")
{
	this->_init();
}

OSModule::~OSModule(void)
{}

void
OSModule::updateModule(void)
{ return; }

void
OSModule::_init(void)
{
	struct utsname			utsname;
	std::stringstream		kernel;

	uname(&utsname);
	kernel << utsname.sysname << " Kernel Version " << utsname.release;
	this->_strings["Name"] = getOsName();
	this->_strings["Kernel version"] = kernel.str();
}
