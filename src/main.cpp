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
#include <VMModule.hpp>

#include <iostream>
#include <fstream>

static IMonitorModule*		CPUModuleCreator(void)
{ return new CPUModule; }

static IMonitorModule*		DateModuleCreator(void)
{ return new DateModule; }

static IMonitorModule*		NetworkModuleCreator(void)
{ return new NetworkModule; }

static IMonitorModule*		OSModuleCreator(void)
{ return new OSModule; }

static IMonitorModule*		RAMModuleCreator(void)
{ return new RAMModule; }

static IMonitorModule*		UserModuleCreator(void)
{ return new UserModule; }

static IMonitorModule*		VMModuleCreator(void)
{ return new VMModule; }

typedef IMonitorModule* (*moduleCreator)(void);

static int					createModules(std::vector<IMonitorModule*>& modules)
{
	std::map<std::string, moduleCreator>	constructors;
	std::map<std::string, bool>				created;

	constructors["CPU"] = CPUModuleCreator;
	constructors["Date"] = DateModuleCreator;
	constructors["Network"] = NetworkModuleCreator;
	constructors["OS"] = OSModuleCreator;
	constructors["RAM"] = RAMModuleCreator;
	constructors["User"] = UserModuleCreator;
	constructors["VM"] = VMModuleCreator;

	for (
			std::map<std::string, moduleCreator>::iterator it = constructors.begin();
			it != constructors.end();
			it++
		)
		created[it->first] = true;

	std::ifstream		config("./modules.config");
	if (!config.is_open())
	{
		std::cout << "Could not open modules.config file" << std::endl;
		return 0;
	}

	while (config)
	{
		std::string		line;

		config >> line;

		if (line == "")
			continue;

		if (constructors[line])
		{
			if (created[line])
			{
				modules.push_back(constructors[line]());
				created[line] = false;
			}
			else
				std::cout << "Module " << line << " is already present" << std::endl;
		}
		else
		{
			std::cout << "Bad module " << line << std::endl;
		}
	}

	if (!modules.size())
		std::cout << "No modules to print" << std::endl;
	return modules.size();
}

static IMonitorDisplay		*get_monitor(std::string option, std::vector<IMonitorModule*>& modules)
{
	if (option == "-t")
		return new NCurses(modules);
	else if (option == "-g")
		return new Sfml(modules);
	else
	{
		std::cout << "Unknown option " << option << std::endl;
		return NULL;
	}
}

int			main(int ac, char **av)
{
	IMonitorDisplay						*monitor;
	std::vector<IMonitorModule*>		modules;

	if (ac != 2)
	{
		std::cout << "./usage <-t | -g>" << std::endl
				  << "\t-t: interface in terminal" << std::endl
				  << "\t-g: interface in gui" << std::endl
				  << "\t-b: both" << std::endl;
		return 0;
	}

	if (!createModules(modules))
		return 0;

	monitor = get_monitor(av[1], modules);

	if (monitor)
		monitor->launch();

	for (
			std::vector<IMonitorModule*>::iterator it = modules.begin();
			it != modules.end();
			it++
		)
		delete *it;
	delete monitor;
}
