#include <DateModule.hpp>

DateModule::DateModule(void):
	AMonitorModule("Date")
{
	this->updateModule();
}

DateModule::~DateModule(void)
{}

void
DateModule::updateModule(void)
{
	time_t					time;
	struct tm				*tm;
	char					date[1024];
	char					clock_time[1024];
	std::stringstream		ss;

	std::time(&time);
	tm = localtime(&time);
	std::strftime(date, 1024, "%d/%m/%Y", tm);
	std::strftime(clock_time, 1024, "%T", tm);
	this->_strings["Date"] = date;
	this->_strings["Time"] = clock_time;
}
