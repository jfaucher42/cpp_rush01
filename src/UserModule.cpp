#include <UserModule.hpp>

UserModule::UserModule(void):
	AMonitorModule("User information")
{
	this->_init();
}

UserModule::~UserModule(void)
{}

void
UserModule::updateModule(void)
{ return; }

void
UserModule::_init(void)
{
	char	username[128];
	char	hostname[128];

	getlogin_r(username, 128);
	this->_strings["Username"] = std::string(username);
	gethostname(hostname, 128);
	this->_strings["Hostname"] = std::string(hostname);
}
