#include "Sfml.hpp"
#include <stdexcept>
#include <vector>
#include <thread>
#include <map>

Sfml::Sfml(std::vector<IMonitorModule*>& modules):
	_modules(modules) {
	this->_x = 1400;
	this->_y = 600;
	this->_line = 1;
	this->_maxLines = 18;
	this->_margin = 50;
	this->_window = new sf::RenderWindow(sf::VideoMode(this->_x, this->_y), "ft_gkrellm", sf::Style::Default, sf::ContextSettings(32));
	this->_window->setFramerateLimit(1);
	this->_font = new sf::Font();
	if (!this->_font->loadFromFile("/Library/Fonts/GillSans.ttc"))
		if (!this->_font->loadFromFile("/Library/Fonts/Arial.ttf"))
			throw std::runtime_error("Can't load font");
	this->_fontSize = 18;
}
Sfml::Sfml(const Sfml & ref) : _modules(ref._modules) { *this = ref; }
Sfml & Sfml::operator=(const Sfml & ref) {
	this->_window = ref.getWindow();
	this->_font = ref.getFont();
	this->_fontSize = ref.getFontSize();
	this->_x = ref.getX();
	this->_y = ref.getY();
	this->_line = ref.getLineNumber();
	this->_maxLines = ref.getMaxLinesNumber();
	this->_margin = ref.getMargin();
	return *this;
}
Sfml::~Sfml() {}

void Sfml::_print(const char *str) {
	sf::Text text;
	text.setFont(*(this->getFont()));
	text.setCharacterSize(this->getFontSize());
	text.setString(str);
	text.setFillColor(sf::Color::Green);
	text.setPosition(this->_margin, (this->_line++) * (this->_fontSize + 10));
	if (this->_line > this->_maxLines) {
		this->_line = 1;
		this->_margin += 425;
	}
	this->getWindow()->draw(text);
}

void Sfml::_printModuleName(std::string const str) {
	sf::Text text;
	text.setFont(*(this->getFont()));
	text.setCharacterSize(this->getFontSize() * 2);
	text.setString(str);
	text.setFillColor(sf::Color::Red);
	text.setPosition(this->_margin, (this->_line) * (this->_fontSize + 10));
	this->_line += 2;
	if (this->_line > this->_maxLines) {
		this->_line = 1;
		this->_margin += 425;
	}
	this->getWindow()->draw(text);
}

void Sfml::_printStrings(std::map<std::string, std::string> const &strings)
{
	for (
			std::map<std::string, std::string>::const_iterator it = strings.begin();
			it != strings.end();
			it++
		)
	{
		std::stringstream		ss;

		ss << it->first << ": " << it->second;
		this->_print(ss.str().c_str());
	}
}

void Sfml::_printNumbers(std::map<std::string, long double> const &numbers)
{
	for (
			std::map<std::string, long double>::const_iterator it = numbers.begin();
			it != numbers.end();
			it++
		)
	{
		std::stringstream		ss;

		ss << it->first << ": " << it->second;
		this->_print(ss.str().c_str());
	}
}

void Sfml::_printData(void) {
	this->_line = 1;
	this->_margin = 50;
	this->_window->clear();
	for (
			std::vector<IMonitorModule*>::iterator it = this->_modules.begin();
			it != this->_modules.end();
			it++
			)
	{
		IMonitorModule		*module = *it;

		this->_printModuleName(module->getName());
		this->_printStrings(module->getStrings());
		this->_printNumbers(module->getNumbers());
		this->_print("\r\n");
	}

	this->_updateModules();
	this->getWindow()->display();
	return;
}

void Sfml::launch(void) {
	sf::Event event;

	this->_window->setActive(true);
	while (this->getWindow()->isOpen()) {
		this->_printData();
		while (this->getWindow()->pollEvent(event)) {
			// Close button: exit
			if (event.type == sf::Event::Closed)
				this->getWindow()->close();

			// Escape key: exit
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				this->getWindow()->close();

			// Resize event: exit
			if (event.type == sf::Event::Resized)
				this->getWindow()->close();
		}
	}
}

sf::RenderWindow *Sfml::getWindow() const { return this->_window; }
sf::Font *Sfml::getFont() const { return this->_font; }
unsigned int Sfml::getFontSize() const { return this->_fontSize; }
unsigned int Sfml::getX() const { return this->_x; }
unsigned int Sfml::getY() const { return this->_y; }
unsigned int Sfml::getLineNumber() const { return this->_line; }
unsigned int Sfml::getMaxLinesNumber() const { return this->_maxLines; }
unsigned int Sfml::getMargin() const { return this->_margin; }


void
Sfml::_updateModules(void)
{
	for (
			std::vector<IMonitorModule*>::const_iterator it = this->_modules.begin();
			it != this->_modules.end();
			it++
		)
		reinterpret_cast<IMonitorModule*>(*it)->updateModule();
}
