/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/21 18:03:36 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FSMLDisplay.hpp"

FSMLDisplay::FSMLDisplay(void) {
    _window = new sf::RenderWindow(
	sf::VideoMode((sf::VideoMode::getDesktopMode().width / 2),
	(sf::VideoMode::getDesktopMode().height)),
	"Nibbler - FSML");
}

FSMLDisplay::~FSMLDisplay(void) {
    delete _window;
}

sf::RenderWindow	*FSMLDisplay::getWindow() const {
    return	_window;
}

void	FSMLDisplay::displayGameWindow(void) {
    std::cout << "DisplayGameWindow called from SFML" << std::endl;
    _window->setPosition(sf::Vector2i(100, 0));
    _window->clear(sf::Color::Black);
    _window->display();
}

void	FSMLDisplay::sayHello(std::string name) {
    std::cout << "This from FSML: hello, " << name << "!" << std::endl;
}

IDisplay *createDisplay(void) {
    return new FSMLDisplay();
}

void	deleteDisplay(IDisplay *disp) {
    delete disp;
}

void	FSMLDisplay::swapDisplay(int newDisplay) {
    //the swap of display must happen in main/outside of the display
    std::cout << "must swap display to " << newDisplay << std::endl;
    _window->close();
}

void	FSMLDisplay::eventLoop(void) {
    sf::Event event;
    std::cout << "start event loop"<< std::endl;
    while (_window->isOpen()) {
	while (_window->pollEvent(event)) {
	    if (event.type == sf::Event::Closed
	    || (event.type == sf::Event::KeyPressed
		&& event.key.code == sf::Keyboard::Escape))
		_window->close();
	    else if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Num2) {
		    FSMLDisplay::swapDisplay(2);
		}
	    }
	    _window->clear(sf::Color::Black);
	    _window->display();
	}
    }
}
