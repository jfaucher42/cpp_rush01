#include <AMonitorModule.hpp>

AMonitorModule::AMonitorModule(std::string name):
	_name(name)
{}

AMonitorModule::~AMonitorModule(void)
{}

std::string const
AMonitorModule::getName(void) const
{ return this->_name; }

std::map<std::string, std::string> const
AMonitorModule::getStrings(void) const
{
	return this->_strings;
}

std::map<std::string, long double> const
AMonitorModule::getNumbers(void) const
{
	return this->_numbers;
}
