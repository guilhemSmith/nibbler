/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLDisplay.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:20:13 by tbehra            #+#    #+#             */
/*   Updated: 2020/01/12 12:08:40 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_DISPLAY_HPP
# define SFML_DISPLAY_HPP

# include <iostream>
# include <SFML/Graphics.hpp>
# include <map>
# include "IDisplay.hpp"
# define WIDTH_CELL 20
# define HEIGHT_CELL 20
# define WIDTH_CELL_F 20.0
# define HEIGHT_CELL_F 20.0
# define ORIG_SPRITE_SIZE 64
# define ORIG_SPRITE_SIZE_F 64.0

class	SFMLDisplay: public IDisplay {
public:
	enum	spriteMotif {
		obstacle,
		apple,
		blueberry,
		snakeHorizontal,
		snakeVertical,
		snakeHeadTop,
		snakeHeadBottom,
		snakeHeadLeft,
		snakeHeadRight,
		snakeTailTop,
		snakeTailBottom,
		snakeTailLeft,
		snakeTailRight,
		snakeBendTopLeft,
		snakeBendTopRight,
		snakeBendBottomLeft,
		snakeBendBottomRight
	};

	SFMLDisplay(void);
 	~SFMLDisplay(void);

	void						newWindow(size_t x, size_t y);
	void						clearDisplay(void);
	void						refreshDisplay(void);
	void						drawStatic(Position & pos, EMotif motif);
	void						drawMobile(Position & pos, Direction & dest, \
								Direction & from, EMotif motif, float progression);
	void						drawScore(int score);
	EEvent 						pollEvent(void);

private:
	SFMLDisplay(SFMLDisplay const &src);
	SFMLDisplay 				&operator=(SFMLDisplay const &rhs);
	sf::RenderWindow			*_window;
	sf::Font					_font;
	int							_scoreOffset;
	bool						_spritesAvailable;
	bool						_drawTail;
	sf::Texture					_spritesArray;
	
	sf::Sprite					*tryGetSpriteStatic(EMotif motif);
	sf::Sprite					*tryGetSpriteMobile(Direction & dir,
									Direction & from, EMotif motif);
	bool						isMobileSnakePosition(EMotif motif);
	std::pair<size_t, size_t>	getMobileSpritePosition(Direction & dir,
									Direction & from, EMotif motif);	
	void						drawNeck(Position & pos, Direction & dest, \
								Direction & from, float progression);

	const static std::map<sf::Keyboard::Key, IDisplay::EEvent> keyboardToEvent;
	const static std::map<IDisplay::EMotif, sf::Color> motifToColor;
	const static std::map<IDisplay::EMotif, std::pair<size_t, size_t>>
		motifToStaticSpritePosition;
	const static std::map<spriteMotif, std::pair<size_t, size_t>>
		spriteMotifToSpritePosition;
};

extern "C" {
    IDisplay			*createDisplay(void);
    void				deleteDisplay(IDisplay *disp);
}

#endif
