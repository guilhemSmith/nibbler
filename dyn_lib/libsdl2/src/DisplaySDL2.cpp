/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:38 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 15:25:06 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DisplaySDL2.hpp"

DisplaySDL2::DisplaySDL2(void) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		
	}
}

DisplaySDL2::DisplaySDL2(DisplaySDL2 const & rhs) {}

DisplaySDL2::~DisplaySDL2(void) {}

DisplaySDL2 const &	DisplaySDL2::operator=(DisplaySDL2 const & rhs) {}

void				DisplaySDL2::newWindow(size_t x, size_t y) {}

void				DisplaySDL2::refreshDisplay(void) {}

void				DisplaySDL2::drawStatic(Position pos, EMotif motif) {}

void				DisplaySDL2::drawMobile(Position start, Position stop, \
						EMotif color, int progression) {}

void				DisplaySDL2::drawScore(int score) {}

IDisplay::EEvent	DisplaySDL2::pollEvent(void) {
	return None;
}