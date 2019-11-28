/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:38 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/28 15:07:25 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "DisplaySDL2.hpp"

std::map<SDL_Scancode, IDisplay::EEvent> const DisplaySDL2::keyMap = {
	{SDL_SCANCODE_1, One},
	{SDL_SCANCODE_2, Two},
	{SDL_SCANCODE_3, Three},
	{SDL_SCANCODE_UP, Up},
	{SDL_SCANCODE_W, Up},
	{SDL_SCANCODE_DOWN, Down},
	{SDL_SCANCODE_S, Down},
	{SDL_SCANCODE_LEFT, Left},
	{SDL_SCANCODE_A, Left},
	{SDL_SCANCODE_RIGHT, Left},
	{SDL_SCANCODE_D, Left},
	{SDL_SCANCODE_ESCAPE, Quit},
};

DisplaySDL2::DisplaySDL2(void): width(0), height(0), wind(NULL), surf(NULL) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw SDL2Except("Failed to init SDL2");
	}
}

DisplaySDL2::DisplaySDL2(DisplaySDL2 const & rhs): width(rhs.width), \
						height(rhs.height), wind(NULL) {}

DisplaySDL2::~DisplaySDL2(void) {
	if (this->wind != NULL) {
		SDL_DestroyWindow(this->wind);
		this->wind = NULL;
	}
	SDL_Quit();
}

DisplaySDL2 const &	DisplaySDL2::operator=(DisplaySDL2 const & rhs) {
	this->width = rhs.width;
	this->height = rhs.height;
	this->wind = NULL;
	return *this;
}

void				DisplaySDL2::newWindow(size_t x, size_t y) {
	if (this->wind != NULL) {
		SDL_DestroyWindow(this->wind);
		this->wind = NULL;
		this->surf = NULL;
	}
	this->width = x;
	this->height = y;
	this->wind = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_UNDEFINED, \
						SDL_WINDOWPOS_UNDEFINED, x * DisplaySDL2::cell_size, \
						y * DisplaySDL2::cell_size, SDL_WINDOW_SHOWN \
						| SDL_WINDOW_INPUT_FOCUS);
	if (this->wind == NULL) {
		throw SDL2Except("Failed to create an SDL2 window");
	}
	this->surf = SDL_GetWindowSurface(this->wind);
	SDL_FillRect( this->surf, NULL, \
		SDL_MapRGB(this->surf->format, 0x00, 0x00, 0x00));
	this->refreshDisplay();
}

void				DisplaySDL2::refreshDisplay(void) {
	if (this->wind != NULL) {
		SDL_UpdateWindowSurface(this->wind);
	}
}

void				DisplaySDL2::drawStatic(t_position pos, EMotif motif) {
	(void)pos;
	(void)motif;
}

void				DisplaySDL2::drawMobile(t_position start, t_position stop, \
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
	SDL_Event		event;
	
	if (SDL_PollEvent(&event)) {
		if (event.type == SDL_WINDOWEVENT) {
			return this->pollWindowEvent(event);
		}
		if (event.type == SDL_KEYDOWN) {
			return this->pollKeyDownEvent(event);
		}
		return this->pollEvent();
	};
	return None;
}

IDisplay::EEvent				DisplaySDL2::pollWindowEvent(SDL_Event event)  {
	if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
		return Quit;
	}
	return this->pollEvent();
}

IDisplay::EEvent				DisplaySDL2::pollKeyDownEvent(SDL_Event event) {
	try {
		return DisplaySDL2::keyMap.at(event.key.keysym.scancode);
	} catch (std::out_of_range oor) {
		return this->pollEvent();
	}
}

DisplaySDL2::SDL2Except::SDL2Except(std::string message): message(message) {
	char const *	err = SDL_GetError();
	if (err == NULL) {
		this->message += '.';
	}
	std::string str(err);
	this->message += ": " + str;
}

DisplaySDL2::SDL2Except::~SDL2Except(void) {}

DisplaySDL2::SDL2Except::SDL2Except(SDL2Except const & rhs): \
						message(rhs.message) {}

char const *		DisplaySDL2::SDL2Except::what(void) const throw() {
	return this->message.c_str();
}