/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:22 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 15:06:48 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYSDL2_HPP
# define DISPLAYSDL2_HPP

# include <SDL2/SDL.h>
# include "IDisplay.hpp"

class DisplaySDL2: IDisplay {
public:
	DisplaySDL2(void);
	DisplaySDL2(DisplaySDL2 const & rhs);
	~DisplaySDL2(void);

	DisplaySDL2 const &	operator=(DisplaySDL2 const & rhs);

	void				newWindow(size_t x, size_t y);
	void				refreshDisplay(void);
	void				drawStatic(Position pos, EMotif motif);
	void				drawMobile(Position start, Position stop, \
							EMotif color, int progression);
	void				drawScore(int score);
	EEvent 				pollEvent(void);
private:
};

#endif