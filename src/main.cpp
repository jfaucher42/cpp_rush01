#include <IMonitorDisplay.hpp>
#include <IMonitorModule.hpp>

#include <NCurses.hpp>
#include <CPUModule.hpp>

#include <iostream>

static void		update_modules(std::vector<IMonitorModule*> const &modules)
{
	for (
			std::vector<IMonitorModule*>::const_iterator it = modules.begin();
			it != modules.end();
			it++
		)
		reinterpret_cast<IMonitorModule*>(*it)->updateModule();
}

int				main()
{
	std::vector<IMonitorDisplay*>		monitors;
	std::vector<IMonitorModule*>		modules;
	time_t								old_time;
	time_t								actual_time;

	modules.push_back(new CPUModule);
	monitors.push_back(new NCurses(modules));

	std::time(&old_time);
	while (monitors.size())
	{
		for (
				std::vector<IMonitorDisplay*>::iterator it = monitors.begin();
				it != monitors.end();
				it++
			)
		{
			reinterpret_cast<IMonitorDisplay*>(*it)->refreshMonitor();
			std::time(&actual_time);
			if (actual_time != old_time)
				update_modules(modules);
		}
	}

	for (
			std::vector<IMonitorDisplay*>::iterator it = monitors.begin();
			it != monitors.end();
			it++
		)
		delete *it;
}
