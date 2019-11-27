/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:38 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 17:03:11 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DisplaySDL2.hpp"

DisplaySDL2::DisplaySDL2(void): width(0), height(0), window(NULL) {
	if (SDL_Init(SDL_INIT_VIDEO)) {
		throw SDL2Except("Failed to init SDL.");
	}
}

DisplaySDL2::DisplaySDL2(DisplaySDL2 const & rhs): width(rhs.width), \
						height(rhs.height), window(NULL) {}

DisplaySDL2::~DisplaySDL2(void) {
	if (this->window != NULL) {
		SDL_DestroyWindow(this->window);
		this->window = NULL;
	}
	SDL_Quit();
}

DisplaySDL2 const &	DisplaySDL2::operator=(DisplaySDL2 const & rhs) {
	this->width = rhs.width;
	this->height = rhs.height;
	this->window = NULL;
	return *this;
}

void				DisplaySDL2::newWindow(size_t x, size_t y) {
	this->width = x;
	this->height = y;
	this->window = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_UNDEFINED, \
						SDL_WINDOWPOS_UNDEFINED, x * DisplaySDL2::cell_size, \
						y * DisplaySDL2::cell_size, 0);
	if (this->window == NULL) {
		throw SDL2Except("Failed to create an SDL2 window.");
	}
}

void				DisplaySDL2::refreshDisplay(void) {}

void				DisplaySDL2::drawStatic(Position pos, EMotif motif) {
	(void)pos;
	(void)motif;
}

void				DisplaySDL2::drawMobile(Position start, Position stop, \
						EMotif color, int progression) {
	(void)start;
	(void)stop;
	(void)color;
	(void)progression;
}

void				DisplaySDL2::drawScore(int score) {
	(void)score;
}

IDisplay::EEvent	DisplaySDL2::pollEvent(void) {
	return None;
}

DisplaySDL2::SDL2Except::SDL2Except(std::string message) {
	this->message += message;
}