/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDisplay.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:19:27 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 12:08:57 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

# include "Position.hpp"


class IDisplay {
public:
	enum EMotif {
		obstacle,
		apple,
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

	virtual void		newWindow(size_t x, size_t y) = 0;
	virtual void		refreshDisplay(void) = 0;
	virtual void		drawStatic(size_t x, size_t y, EMotif motif) = 0;
	virtual void		drawMobile(Position start, Position stop, \
							EMotif color, int progression) = 0;
	virtual void		drawScore(int score) = 0;
	virtual EEvent 		pollEvent(void) = 0;
};

#endif