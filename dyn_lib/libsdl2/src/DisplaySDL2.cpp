/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:38 by gsmith            #+#    #+#             */
/*   Updated: 2020/03/04 16:56:28 by gsmith           ###   ########.fr       */
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
	{SDL_SCANCODE_RIGHT, Right},
	{SDL_SCANCODE_D, Right},
	{SDL_SCANCODE_ESCAPE, Quit},
};

DisplaySDL2::DisplaySDL2(void): width(0), height(0), wind(NULL), surf(NULL), \
					motifMap(), font(NULL), score_pos() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		throw SDL2Except("Failed to init SDL2");
	}
	if (TTF_Init() < 0) {
		throw SDL2Except("Failed to init SDL2_TTF");
	}
	this->font = TTF_OpenFont("/Library/Fonts/Arial.ttf", \
		DisplaySDL2::cell_size - 2);
	if (this->font == NULL) {
		throw SDL2Except("Failed to load font.");
	}
}

DisplaySDL2::~DisplaySDL2(void) {
	if (this->wind != NULL) {
		SDL_DestroyWindow(this->wind);
		this->wind = NULL;
	}
	TTF_CloseFont(this->font);
	TTF_Quit();
	SDL_Quit();
}

void				DisplaySDL2::newWindow(size_t x, size_t y) {
	if (this->wind != NULL) {
		SDL_DestroyWindow(this->wind);
		this->wind = NULL;
		this->surf = NULL;
	}
	this->width = x;
	this->height = y;
	this->wind = SDL_CreateWindow("Nibbler", SDL_WINDOWPOS_CENTERED, \
						SDL_WINDOWPOS_CENTERED, x * DisplaySDL2::cell_size, \
						y * DisplaySDL2::cell_size + DisplaySDL2::cell_size, \
						SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS);
	if (this->wind == NULL) {
		throw SDL2Except("Failed to create an SDL2 window");
	}
	this->surf = SDL_GetWindowSurface(this->wind);
	this->motifMap = {
		{snakeHead, SDL_MapRGB(this->surf->format, 164, 198, 57)},
		{snake, SDL_MapRGB(this->surf->format, 135, 169, 107)},
		{apple, SDL_MapRGB(this->surf->format, 227, 38, 54)},
		{blueberry, SDL_MapRGB(this->surf->format, 33, 171, 205)},
		{obstacle, SDL_MapRGB(this->surf->format, 159, 129, 112)},
	};
	this->score_pos.x = 1;
	this->score_pos.y = y * DisplaySDL2::cell_size + 1;
	this->score_pos.w = DisplaySDL2::cell_size - 2;
	this->score_pos.h = DisplaySDL2::cell_size - 2;
	this->clearDisplay();
	this->refreshDisplay();
}

void				DisplaySDL2::clearDisplay(void) {
	SDL_FillRect(this->surf, NULL, \
		SDL_MapRGB(this->surf->format, 0x00, 0x00, 0x00));
}

void				DisplaySDL2::refreshDisplay(void) {
	if (this->wind != NULL) {
		SDL_UpdateWindowSurface(this->wind);
	}
}

void				DisplaySDL2::drawStatic(Position & pos, EMotif motif) {
	Uint32			color;
	SDL_Rect		rect = {
		static_cast<int>(pos.x * DisplaySDL2::cell_size),
		static_cast<int>(pos.y * DisplaySDL2::cell_size),
		DisplaySDL2::cell_size,
		DisplaySDL2::cell_size,
	};
	
	try {
		color = this->motifMap.at(motif);
	} catch(std::out_of_range oor) {
		throw SDL2Except("Trying to render an unknown motif");
	}
	SDL_FillRect(this->surf, &rect, color);
}

void				DisplaySDL2::drawMobile(Position & pos, Direction & dest, \
							Direction & from, EMotif motif, float progression) {
	(void)from;
	
	Uint32			color;
	SDL_Rect		rect = {
		static_cast<int>(pos.x * DisplaySDL2::cell_size \
			+ dest.x * progression * DisplaySDL2::cell_size),
		static_cast<int>(pos.y * DisplaySDL2::cell_size \
			+ dest.y * progression * DisplaySDL2::cell_size),
		DisplaySDL2::cell_size,
		DisplaySDL2::cell_size,
	};

	try {
		color = this->motifMap.at(motif);
	} catch(std::out_of_range oor) {
		throw SDL2Except("Trying to render an unknown motif");
	}
	SDL_FillRect(this->surf, &rect, color);
	int new_x = pos.x + dest.x;
	if (new_x == (int)this->width) {
		rect.x = 0.0;
		rect.w = progression * DisplaySDL2::cell_size;
		SDL_FillRect(this->surf, &rect, color);
	} else if (new_x < 0) {
		rect.x = (this->width - progression) * DisplaySDL2::cell_size;
		SDL_FillRect(this->surf, &rect, color);
	}
	int new_y = pos.y + dest.y;
	if (new_y == (int)this->height) {
		rect.y = 0.0;
		rect.h = progression * DisplaySDL2::cell_size;
		SDL_FillRect(this->surf, &rect, color);
	} else if (new_y < 0) {
		rect.y = (this->height - progression) * DisplaySDL2::cell_size;
		SDL_FillRect(this->surf, &rect, color);
	}
}

void				DisplaySDL2::drawScore(int score) {
	SDL_Color White = {255, 255, 255, 255};
	std::string value;
	
	try {
		value = std::to_string(score);
	} catch (std::exception e) {
		value = "ERR";
	}
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font, \
		value.c_str(), White);
	SDL_BlitSurface(surfaceMessage, NULL, this->surf, &this->score_pos);
	SDL_FreeSurface(surfaceMessage);
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
	if (err == NULL || err[0] == 0) {
		this->message += '.';
	} else {
		std::string str(err);
		this->message += ": " + str;
	}
}

DisplaySDL2::SDL2Except::~SDL2Except(void) {}

DisplaySDL2::SDL2Except::SDL2Except(SDL2Except const & rhs): \
						message(rhs.message) {}

char const *		DisplaySDL2::SDL2Except::what(void) const throw() {
	return this->message.c_str();
}