#ifndef SFML_H
#define SFML_H
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <sstream>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <algorithm>
#include <iostream>
#include "IMonitorDisplay.hpp"

class Sfml : public IMonitorDisplay
{
private:
	void _print(const char *);
	void _printModuleName(std::string const);
	void _printStrings(std::map<std::string, std::string> const&);
	void _printNumbers(std::map<std::string, long double> const&);
	void _updateModules(void);
	void _printData(void);

	std::vector<IMonitorModule *>& _modules;
	sf::RenderWindow 		*_window;
	sf::Font 						*_font;
	unsigned int				_fontSize;
	unsigned int				_x;
	unsigned int				_y;
	unsigned int				_line;
	unsigned int				_maxLines;
	unsigned int				_margin;

public:
	Sfml(std::vector<IMonitorModule*>& modules);
	Sfml(const Sfml &ref);
	virtual ~Sfml();
	Sfml & operator=(const Sfml &ref);

	virtual void launch();

	sf::RenderWindow *getWindow() const;
	sf::Font *getFont() const;
	unsigned int getFontSize() const;
	unsigned int getX() const;
	unsigned int getY() const;
	unsigned int getLineNumber() const;
	unsigned int getMaxLinesNumber() const;
	unsigned int getMargin() const;
};

#endif /* SFML_H */
