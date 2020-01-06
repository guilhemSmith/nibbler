/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDisplay.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:19:27 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 18:06:34 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include <cstddef>
# include "Position.hpp"
# include "Direction.hpp"

class IDisplay {
public:
	enum EMotif {
		obstacle,
		apple,
		blueberry,
		snake,
		snakeHead,
	};

	enum EEvent {
		None,
		Quit,
		Up,
		Down,
		Left,
		Right,
		Pause,
		One,
		Two,
		Three,
	};

	virtual ~IDisplay(void) {};

	virtual void	newWindow(size_t x, size_t y) = 0;
	virtual void	clearDisplay(void) = 0;
	virtual void	refreshDisplay(void) = 0;
	virtual void	drawStatic(Position & pos, EMotif motif) = 0;
	virtual void	drawMobile(Position & pos, Direction & dest, \
						Direction & from, EMotif motif, float progression) = 0;
	virtual void	drawScore(int score) = 0;
	virtual EEvent 	pollEvent(void) = 0;
};

#endif
