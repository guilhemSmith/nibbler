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
