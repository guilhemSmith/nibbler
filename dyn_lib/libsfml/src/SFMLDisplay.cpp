/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2020/01/07 15:27:27 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SFMLDisplay.hpp"

SFMLDisplay::SFMLDisplay(void): _window(NULL) {
}

SFMLDisplay::~SFMLDisplay(void) {
	if (_window != NULL) {
		std::cout << "delete sfml window in destructor" << std::endl;
		_window->close();
		delete _window;
	} }

const std::map<sf::Keyboard::Key, IDisplay::EEvent> SFMLDisplay::keyboardToEvent = {
	{sf::Keyboard::Num1, IDisplay::EEvent::One},
	{sf::Keyboard::Num2, IDisplay::EEvent::Two},
	{sf::Keyboard::Num3, IDisplay::EEvent::Three},
	{sf::Keyboard::Up, IDisplay::EEvent::Up},
	{sf::Keyboard::Down, IDisplay::EEvent::Down},
	{sf::Keyboard::Left, IDisplay::EEvent::Left},
	{sf::Keyboard::Right, IDisplay::EEvent::Right},
	{sf::Keyboard::Escape, IDisplay::EEvent::Quit},
};

const std::map<IDisplay::EMotif, sf::Color> SFMLDisplay::motifToColor = {
	{IDisplay::EMotif::snake, sf::Color::Red},
	{IDisplay::EMotif::snakeHead, sf::Color::Yellow},
	{IDisplay::EMotif::obstacle, sf::Color::Cyan},
	{IDisplay::EMotif::apple, sf::Color::Green},
	{IDisplay::EMotif::blueberry, sf::Color::Magenta},
};

IDisplay *createDisplay(void) {
	return new SFMLDisplay();
}

void	deleteDisplay(IDisplay *disp) {
	delete disp;
}

void	SFMLDisplay::newWindow(size_t x, size_t y) {
	std::cout << "new window called" << std::endl;
	if (_window) {
		std::cout << "delete sfml window in new window" << std::endl;
		_window->close();
		delete _window;
	}
	if (!_font.loadFromFile("./dyn_lib/libsfml/fonts/Roboto-Regular.ttf")) {
		std::cout << "font \"Roboto-Regular.ttf\" not found" << std::endl;
	}
	_window = new sf::RenderWindow(
			sf::VideoMode(WIDTH_CELL * x, HEIGHT_CELL * (y + 1) + 10),
			"Nibbler - SFML");
	_score_offset = HEIGHT_CELL * y;
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

void	SFMLDisplay::drawStatic(Position & pos, EMotif motif) {
	sf::Color color;

	try {
		color = motifToColor.at(motif);
	}
	catch (std::out_of_range oor) {
		color = sf::Color::Black;
	}
	sf::RectangleShape toDraw(sf::Vector2f(WIDTH_CELL, HEIGHT_CELL));
	toDraw.setFillColor(color);
	toDraw.setPosition(pos.x * WIDTH_CELL, pos.y * HEIGHT_CELL);
	_window->draw(toDraw);
}

void	SFMLDisplay::drawMobile(Position & pos, Direction & dest, \
					Direction & from, EMotif motif, float progression)
{
	(void)from;
	sf::Color color;

	try {
		color = motifToColor.at(motif);
	}
	catch (std::out_of_range oor) {
		color = sf::Color::Black;
	}
	sf::RectangleShape toDraw(sf::Vector2f(WIDTH_CELL, HEIGHT_CELL));
	toDraw.setFillColor(color);
	toDraw.setPosition(
		static_cast<int>(pos.x * WIDTH_CELL + dest.x * progression * WIDTH_CELL),
		static_cast<int>(pos.y * HEIGHT_CELL + dest.y * progression * HEIGHT_CELL)
	);
	_window->draw(toDraw);
}	

void	SFMLDisplay::drawScore(int score) {
	sf::Text text;
	text.setFont(_font);
	text.setString("Score: " + std::to_string(score));
	text.setCharacterSize(HEIGHT_CELL);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, _score_offset);
	_window->draw(text);
}

IDisplay::EEvent SFMLDisplay::pollEvent(void) {
	sf::Event event;
	if (_window == NULL || !_window->isOpen())
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
