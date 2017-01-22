#include <IMonitorDisplay.hpp>
#include <IMonitorModule.hpp>

#include <NCurses.hpp>
#include "Sfml.hpp"

#include <CPUModule.hpp>
#include <DateModule.hpp>
#include <NetworkModule.hpp>
#include <OSModule.hpp>
#include <RAMModule.hpp>
#include <UserModule.hpp>

#include <iostream>
#include <fstream>

static int		createModules(std::vector<IMonitorModule*>& modules)
{
	modules.push_back(new CPUModule);
	modules.push_back(new DateModule);
	modules.push_back(new NetworkModule);
	modules.push_back(new OSModule);
	modules.push_back(new RAMModule);
	modules.push_back(new UserModule);
	return 1;
}

int			main(int ac, char **av)
{
	IMonitorDisplay						*monitor;
	std::vector<IMonitorModule*>		modules;
	bool								ready = true;

	if (ac != 2)
	{
		std::cout << "./usage <-t | -g>" << std::endl
				  << "\t-t: interface in terminal" << std::endl
				  << "\t-g: interface in gui" << std::endl;
		return 0;
	}

	createModules(modules);

	std::string		monitorName(av[1]);
	if (monitorName == "-t")
		monitor = new NCurses(modules);
	else if (monitorName == "-g")
		monitor = new Sfml(modules);

	if (ready)
		monitor->launch();

	for (
			std::vector<IMonitorModule*>::iterator it = modules.begin();
			it != modules.end();
			it++
		)
		delete *it;
	delete monitor;
}
