#ifndef IMONITORDISPLAY_HPP

# define IMONITORDISPLAY_HPP

# include <IMonitorModule.hpp>

class IMonitorDisplay
{
	public:
		// The constructor is supposed to take a std::vector<IMonitorModule*>&
		virtual ~IMonitorDisplay() {}

		virtual void	refreshMonitor(void) = 0;
};

#endif
