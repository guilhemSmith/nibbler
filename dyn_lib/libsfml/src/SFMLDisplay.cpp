/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2020/01/11 17:47:12 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SFMLDisplay.hpp"

SFMLDisplay::SFMLDisplay(void): _window(NULL) {
	_spritesAvailable =
		_spritesArray.loadFromFile("./dyn_lib/libsfml/images/sprites.png");
	_drawTail = true;
}

SFMLDisplay::~SFMLDisplay(void) {
	if (_window != NULL) {
		std::cout << "delete sfml window in destructor" << std::endl;
		_window->setVisible(false);
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
	{sf::Keyboard::Escape, IDisplay::EEvent::Quit},
};

const std::map<IDisplay::EMotif, sf::Color> SFMLDisplay::motifToColor = {
	{IDisplay::EMotif::snake, sf::Color::Red},
	{IDisplay::EMotif::snakeHead, sf::Color::Yellow},
	{IDisplay::EMotif::obstacle, sf::Color::Cyan},
	{IDisplay::EMotif::apple, sf::Color::Green},
	{IDisplay::EMotif::blueberry, sf::Color::Magenta},
};

const std::map<IDisplay::EMotif, std::pair<size_t, size_t>>
		SFMLDisplay::motifToStaticSpritePosition = {
	{IDisplay::EMotif::snake, std::pair<size_t, size_t>(1, 0)},
	{IDisplay::EMotif::snakeHead, std::pair<size_t, size_t>(3, 0)},
	{IDisplay::EMotif::obstacle, std::pair<size_t, size_t>(2, 3)},
	{IDisplay::EMotif::apple, std::pair<size_t, size_t>(0, 3)},
	{IDisplay::EMotif::blueberry, std::pair<size_t, size_t>(1, 3)},
};

const std::map<SFMLDisplay::spriteMotif, std::pair<size_t, size_t>>
		SFMLDisplay::spriteMotifToSpritePosition = {
	{SFMLDisplay::spriteMotif::obstacle, std::pair<size_t, size_t>(2, 3)},
	{SFMLDisplay::spriteMotif::apple, std::pair<size_t, size_t>(0, 3)},
	{SFMLDisplay::spriteMotif::blueberry, std::pair<size_t, size_t>(1, 3)},
	{SFMLDisplay::spriteMotif::snakeHorizontal, std::pair<size_t, size_t>(1, 0)},
	{SFMLDisplay::spriteMotif::snakeVertical, std::pair<size_t, size_t>(2, 1)},
	{SFMLDisplay::spriteMotif::snakeHeadTop, std::pair<size_t, size_t>(3, 0)},
	{SFMLDisplay::spriteMotif::snakeHeadBottom, std::pair<size_t, size_t>(4, 1)},
	{SFMLDisplay::spriteMotif::snakeHeadLeft, std::pair<size_t, size_t>(3, 1)},
	{SFMLDisplay::spriteMotif::snakeHeadRight, std::pair<size_t, size_t>(4, 0)},
	{SFMLDisplay::spriteMotif::snakeTailTop, std::pair<size_t, size_t>(3, 2)},
	{SFMLDisplay::spriteMotif::snakeTailBottom, std::pair<size_t, size_t>(4, 3)},
	{SFMLDisplay::spriteMotif::snakeTailLeft, std::pair<size_t, size_t>(3, 3)},
	{SFMLDisplay::spriteMotif::snakeTailRight, std::pair<size_t, size_t>(4, 2)},
	{SFMLDisplay::spriteMotif::snakeBendTopLeft, std::pair<size_t, size_t>(0, 0)},
	{SFMLDisplay::spriteMotif::snakeBendTopRight, std::pair<size_t, size_t>(2, 0)},
	{SFMLDisplay::spriteMotif::snakeBendBottomLeft, std::pair<size_t, size_t>(0, 1)},
	{SFMLDisplay::spriteMotif::snakeBendBottomRight, std::pair<size_t, size_t>(2, 2)},
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
	_scoreOffset = HEIGHT_CELL * y;
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

sf::Sprite *SFMLDisplay::tryGetSpriteStatic(EMotif motif) {
	if (!_spritesAvailable)
		return (NULL);
	try {
		std::pair<size_t, size_t> spritePos = motifToStaticSpritePosition.at(motif);
		return (new sf::Sprite(_spritesArray, 
			sf::IntRect(ORIG_SPRITE_SIZE * std::get<0>(spritePos),
				ORIG_SPRITE_SIZE * std::get<1>(spritePos),
				ORIG_SPRITE_SIZE, ORIG_SPRITE_SIZE)));
	}
	catch (std::exception e) {
		return (NULL);
	}
	return (NULL);
}

void	SFMLDisplay::drawStatic(Position & pos, EMotif motif) {
	sf::Color color;
	sf::Sprite *sprite;

	sprite = tryGetSpriteStatic(motif);
	if (sprite != NULL) {
		sprite->setScale(sf::Vector2f(WIDTH_CELL_F/ORIG_SPRITE_SIZE_F,
					HEIGHT_CELL_F/ORIG_SPRITE_SIZE_F));
		sprite->setPosition(pos.x * WIDTH_CELL, pos.y * HEIGHT_CELL);
		sprite->setScale(sf::Vector2f(WIDTH_CELL_F/ORIG_SPRITE_SIZE_F,
					HEIGHT_CELL_F/ORIG_SPRITE_SIZE_F));
		_window->draw(*sprite);
		delete sprite;
	}
	else {
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
}

std::pair<size_t, size_t> SFMLDisplay::getMobileSpritePosition(Direction & dir,
		Direction & from, EMotif motif) {
	SFMLDisplay::spriteMotif res;

	if (motif == IDisplay::EMotif::snakeHead) {
		if (dir.x == 1 && dir.y == 0) 
			res = snakeHeadRight;
		else if (dir.x == -1 && dir.y == 0)
			res = snakeHeadLeft;
		else if (dir.x == 0 && dir.y == -1)
			res = snakeHeadTop;
		else if (dir.x == 0 && dir.y == 1)
			res = snakeHeadBottom;
		_drawTail = true;
	}
	else if (motif == IDisplay::EMotif::snake) {
		if (_drawTail) {
			if (dir.x == 0 && dir.y == 1) 
				res = snakeTailBottom;
			else if (dir.x == 0 && dir.y == -1)
				res = snakeTailTop;
			else if (dir.x == -1 && dir.y == 0)
				res = snakeTailLeft;
			else if (dir.x == 1 && dir.y == 0)
				res = snakeTailRight;
			_drawTail = false;
		}
		else if (from.x != dir.x || from.y != dir.y)
		{
			if ((from.x == -1 && dir.y == 1) || (from.y == -1 && dir.x == 1))
				res = snakeBendTopLeft;
			else if ((from.y == -1 && dir.x == -1) || (from.x == 1 && dir.y == 1))
				res = snakeBendTopRight;
			else if ((from.x == 1 && dir.y == -1) || (from.y == 1 && dir.x == -1))
				res = snakeBendBottomRight;
			else
				res = snakeBendBottomLeft;
		}
		else {
			res = (dir.x == 0) ? snakeVertical : snakeHorizontal;
		}
	}
	else {
		if (motif == IDisplay::EMotif::obstacle) 
			res = obstacle;
		else if (motif == IDisplay::EMotif::apple) 
			res = apple;
		else if (motif == IDisplay::EMotif::blueberry) 
			res = blueberry;
	}
	return spriteMotifToSpritePosition.at(res);
}

sf::Sprite *SFMLDisplay::tryGetSpriteMobile(Direction & dir,
		Direction & from, EMotif motif) {
	if (!_spritesAvailable)
		return (NULL);
	try {
		std::pair<size_t, size_t> spritePos = getMobileSpritePosition(dir, from,
				motif);
		return (new sf::Sprite(_spritesArray, 
			sf::IntRect(ORIG_SPRITE_SIZE * (std::get<0>(spritePos)),
				ORIG_SPRITE_SIZE * (std::get<1>(spritePos)),
				ORIG_SPRITE_SIZE, ORIG_SPRITE_SIZE)));
	}
	catch (std::exception e) {
		return (NULL);
	}
	return (NULL);
}

bool	SFMLDisplay::isMobileSnakePosition(EMotif motif) {
	if (_drawTail) {
		return (true);
	}
	return (motif == IDisplay::EMotif::snakeHead);
}

void	SFMLDisplay::drawMobile(Position & pos, Direction & dest, \
					Direction & from, EMotif motif, float progression)
{
	sf::Color color;
	sf::Sprite *sprite;

	sprite = tryGetSpriteMobile(dest, from, motif);
	if (sprite != NULL) {
		sprite->setScale(sf::Vector2f(WIDTH_CELL_F/ORIG_SPRITE_SIZE_F,
					HEIGHT_CELL_F/ORIG_SPRITE_SIZE_F));
		if (isMobileSnakePosition(motif)) {
			sprite->setPosition(
				pos.x * WIDTH_CELL + dest.x * progression * WIDTH_CELL,
				pos.y * HEIGHT_CELL + dest.y * progression * HEIGHT_CELL);
		}
		else {
			sprite->setPosition(
				pos.x * WIDTH_CELL + dest.x,
				pos.y * HEIGHT_CELL + dest.y);
		}
		sprite->setScale(sf::Vector2f(WIDTH_CELL_F/ORIG_SPRITE_SIZE_F,
					HEIGHT_CELL_F/ORIG_SPRITE_SIZE_F));
		_window->draw(*sprite);
		delete sprite;
	}
	else {
		try {
			color = motifToColor.at(motif);
		}
		catch (std::out_of_range oor) {
			color = sf::Color::Black;
		}
		sf::RectangleShape toDraw(sf::Vector2f(WIDTH_CELL, HEIGHT_CELL));
		toDraw.setFillColor(color);
		toDraw.setPosition(
			static_cast<int>(pos.x * WIDTH_CELL
				+ dest.x * progression * WIDTH_CELL),
			static_cast<int>(pos.y * HEIGHT_CELL
				+ dest.y * progression * HEIGHT_CELL)
			);
		_window->draw(toDraw);
	}
}	

void	SFMLDisplay::drawScore(int score) {
	sf::Text text;
	text.setFont(_font);
	text.setString("Score: " + std::to_string(score));
	text.setCharacterSize(HEIGHT_CELL);
	text.setFillColor(sf::Color::White);
	text.setPosition(10, _scoreOffset);
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
				if (event.key.code == sf::Keyboard::Num3)
				{
					// doesn't work ! Find why
					std::cout << "here"<< std::endl;
					_window->setVisible(false);
				}

				return this->keyboardToEvent.at(event.key.code);
			}
			catch (std::out_of_range &oor) {
				continue;
			}
		}
	}	
	return (None);
}
