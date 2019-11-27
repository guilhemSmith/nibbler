/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/27 13:36:18 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FSMLDisplay.hpp"

FSMLDisplay::FSMLDisplay(void): _window(NULL) {
}

FSMLDisplay::~FSMLDisplay(void) {
    delete _window;
}

IDisplay *createDisplay(void) {
    return new FSMLDisplay();
}

void	deleteDisplay(IDisplay *disp) {
    delete disp;
}

void	FSMLDisplay::newWindow(size_t x, size_t y) {
    std::cout << "New window called from SFML" << std::endl;

	(void)x;
	(void)y;

	if (_window)
		_window->close();
    _window = new sf::RenderWindow(
			sf::VideoMode((sf::VideoMode::getDesktopMode().width),
			(sf::VideoMode::getDesktopMode().height)),
			"Nibbler - FSML");

    _window->setPosition(sf::Vector2i(100, 0));
    _window->clear(sf::Color::Black);
    _window->display();
}

void	FSMLDisplay::refreshDisplay(void) {
    _window->display();
}

void	FSMLDisplay::drawStatic(Position pos, EMotif motif) {
	(void)pos;
	(void)motif;
}

void	FSMLDisplay::drawMobile(Position start, Position stop, EMotif motif,
			int progression)
{
	(void)start;
	(void)stop;
	(void)motif;
	(void)progression;
}	

void	FSMLDisplay::drawScore(int score) {
	(void)score;
}

FSMLDisplay::EEvent FSMLDisplay::pollEvent(void) {
	return None;
}



/*
 *
    _window = new sf::RenderWindow(
		sf::VideoMode((sf::VideoMode::getDesktopMode().width / 2),
	(sf::VideoMode::getDesktopMode().height)),
	"Nibbler - FSML");
void	FSMLDisplay::displayGameWindow(void) {
    std::cout << "DisplayGameWindow called from SFML" << std::endl;
    _window->setPosition(sf::Vector2i(100, 0));
    _window->clear(sf::Color::Black);
    _window->display();
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
*/
