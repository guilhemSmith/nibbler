/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/27 18:27:50 by tbehra           ###   ########.fr       */
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

void	FSMLDisplay::clearDisplay(void) {
	_window->clear(sf::Color::Black);
}

void	FSMLDisplay::drawStatic(t_position pos, EMotif motif) {
	sf::Color color;
	switch (motif) {
		case snake:
			color = sf::Color::Red;	
			break;
		case snakeHead:
			color = sf::Color::Yellow;	
			break;
		case obstacle:
			color = sf::Color::Cyan;	
			break;
		case apple:
			color = sf::Color::Green;
			break;
		default:
			color = sf::Color::Black;
	}
	sf::RectangleShape toDraw(sf::Vector2f(WIDTH_CELL, HEIGHT_CELL));
	toDraw.setFillColor(color);
	toDraw.setPosition(pos.x * WIDTH_CELL, pos.y * HEIGHT_CELL);
	_window->draw(toDraw);
}

void	FSMLDisplay::drawMobile(t_position start, t_position stop, EMotif motif,
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
	sf::Event event;
	if (!_window->isOpen())
		return None;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			_window->close();
			return Quit;
		}
		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Num2)
				return Two;
			if (event.key.code == sf::Keyboard::Up)
				return Up;
			if (event.key.code == sf::Keyboard::Down)
				return Down;
			if (event.key.code == sf::Keyboard::Left)
				return Left;
			if (event.key.code == sf::Keyboard::Right)
				return Right;
		}
	}	
	return (None);
}
