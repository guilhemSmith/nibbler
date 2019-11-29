/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/29 15:02:11 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SFMLDisplay.hpp"

SFMLDisplay::SFMLDisplay(void): _window(NULL) {
}

SFMLDisplay::~SFMLDisplay(void) {
	if (_window != NULL) {
		_window->close();
		delete _window;
	}
}

const std::map<sf::Keyboard::Key, IDisplay::EEvent> SFMLDisplay::keyboardToEvent = {
	{sf::Keyboard::Num1, IDisplay::EEvent::One},
	{sf::Keyboard::Num2, IDisplay::EEvent::Two},
	{sf::Keyboard::Num3, IDisplay::EEvent::Three},
	{sf::Keyboard::Up, IDisplay::EEvent::Up},
	{sf::Keyboard::Down, IDisplay::EEvent::Down},
	{sf::Keyboard::Left, IDisplay::EEvent::Left},
	{sf::Keyboard::Right, IDisplay::EEvent::Right},
};

IDisplay *createDisplay(void) {
	return new SFMLDisplay();
}

void	deleteDisplay(IDisplay *disp) {
	delete disp;
}

void	SFMLDisplay::newWindow(size_t x, size_t y) {
	std::cout << "New window called from SFML" << std::endl;
	if (_window) {
		_window->close();
		delete _window;
	}
	_window = new sf::RenderWindow(
			sf::VideoMode(WIDTH_CELL * x, HEIGHT_CELL * y),
			"Nibbler - SFML");
	_window->setPosition(sf::Vector2i(100, 0));
	_window->clear(sf::Color::Black);
	_window->display();
}

void	SFMLDisplay::refreshDisplay(void) {
	_window->display();
}

void	SFMLDisplay::clearDisplay(void) {
	_window->clear(sf::Color::Black);
}

void	SFMLDisplay::drawStatic(t_position pos, EMotif motif) {
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

void	SFMLDisplay::drawMobile(t_position start, t_position stop, EMotif motif,
		int progression)
{
	(void)start;
	(void)stop;
	(void)motif;
	(void)progression;
}	

void	SFMLDisplay::drawScore(int score) {
	(void)score;
}


IDisplay::EEvent SFMLDisplay::pollEvent(void) {
	sf::Event event;
	if (!_window->isOpen())
		return None;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
		{
			return Quit;
		}
		if (event.type == sf::Event::KeyPressed) {
			try {
				return this->keyboardToEvent.at(event.key.code);
			}
			catch (std::out_of_range &oor) {
				continue;
			}
		}
	}	
	return (None);
}
