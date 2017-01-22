#include "Sfml.hpp"

Sfml::Sfml (std::vector<IMonitorModule*>& modules): _modules(modules) {
	this->_x = 800;
	this->_y = 600;
	this->_window = new sf::Window(sf::VideoMode(this->_x, this->_y), "ft_gkrellm");
}
Sfml::Sfml(const Sfml & ref) : _modules(ref._modules) { *this = ref; }
Sfml & Sfml::operator=(const Sfml & ref) {
	this->_window = ref.getWindow();
	this->_x = ref.getX();
	this->_y = ref.getY();
	return *this;
}
Sfml::~Sfml() {}

void Sfml::_print(const char *) const {

}

void Sfml::launch(void) {
	while (this->getWindow()->isOpen()) {
		sf::Event event;
		while (this->getWindow()->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				this->getWindow()->close();
			}
		}
	}
}

sf::Window *Sfml::getWindow() const { return this->_window; }
unsigned int Sfml::getX() const { return this->_x; }
unsigned int Sfml::getY() const { return this->_y; }
