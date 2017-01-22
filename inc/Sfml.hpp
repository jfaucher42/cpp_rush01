#ifndef SFML_H
#define SFML_H
#include <SFML/Window.hpp>
#include <algorithm>
#include "IMonitorDisplay.hpp"

class Sfml : public IMonitorDisplay
{
private:
	void _print(const char *) const;

	std::vector<IMonitorModule *>& _modules;
	sf::Window 		*_window;
	unsigned int 	_x;
	unsigned int 	_y;

public:
	Sfml(std::vector<IMonitorModule*>& modules);
	Sfml(const Sfml &ref);
	virtual ~Sfml();
	Sfml & operator=(const Sfml &ref);

	virtual void launch();

	sf::Window *getWindow() const;
	unsigned int getX() const;
	unsigned int getY() const;
};

#endif /* SFML_H */
