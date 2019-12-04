/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:47 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/04 18:03:11 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ctime>
#include <iostream>
#include "Game.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Obstacle.hpp"

Game::Game(int lib, size_t width, size_t height): \
				paused(false), score(0), dir(Direction(0, 1)), \
				dir_next(Direction(0, 0)), frame(0), speed(SPEED_START), \
				loader(lib, width, height), grid(Grid(width, height)) {
	for (size_t i = 0; i < width; i++){
		this->spawn_obstacle(i, 0);
		this->spawn_obstacle(i, height - 1);
	}

	// for (size_t i = 1; i < height - 1; i++) {
	// 	this->spawn_obstacle(0, i);
	// 	this->spawn_obstacle(width - 1, i);
	// }

	this->spawn_obstacle(width / 3, height / 2);
	this->spawn_apple(width / 2 + 5, height / 2);
	this->spawn_apple(width / 2 + 6, height / 2);
	this->spawn_apple(width / 2 + 7, height / 2);
}

Game::~Game(void) {}

bool			Game::spawn_obstacle(size_t x, size_t y) {
	Obstacle *	obs = new Obstacle();

	if (!this->grid.spawn(obs, x, y)) {
		delete obs;
		return false;
	}
	return true;
}

bool			Game::spawn_apple(size_t x, size_t y) {
	Apple *	apl = new Apple(this->score);

	if (!this->grid.spawn(apl, x, y)) {
		delete apl;
		return false;
	}
	return true;
}

bool			Game::spawn_snake(size_t x, size_t y, int dir_x, int dir_y) {
	Snake *	snk = new Snake(dir_x, dir_y);

	if (!this->grid.spawn(snk, x, y)) {
		delete snk;
		return false;
	}
	return true;
}

bool			Game::run(void) {
	IDisplay::EEvent	event;
	IDisplay *			disp = this->loader.get_display();
	size_t				time_start = time(0);

	while ((event = disp->pollEvent()) != IDisplay::None) {
		if (event == IDisplay::Quit) {
			return false;
		}
		if (event >= IDisplay::Up && event <= IDisplay::Right) {
			this->update_dir(event);
		}
		if (event >= IDisplay::One && event <= IDisplay::Three) {
			try {
				this->loader.load_lib(event - IDisplay::One + 1, \
					this->grid.get_width(), this->grid.get_height());
			} catch (std::exception & e) {
				std::cerr << e.what() << std::endl;
			}
			disp = this->loader.get_display();
		}
	}
	this->frame += 1;
	if (this->frame == this->speed) {
		this->dir_next.clamp();
		if (this->dir_next.length() != 0) {
			if (!this->dir.is_opposed_to(this->dir_next)) {
				this->dir = this->dir_next;
			}
			this->dir_next = Direction(0, 0);
		}
		this->grid.move_head(this->dir.x, this->dir.y);
		frame = 0;
	} 
	usleep(Game::disp_freq - (time(0) - time_start));
	this->grid.print(this->loader.get_display());
	return true;
}

void			Game::update_dir(IDisplay::EEvent event) {
	if (event == IDisplay::Up) {
		this->dir_next.y--;
	}
	if (event == IDisplay::Down) {
		this->dir_next.y++;
	}
	if (event == IDisplay::Left) {
		this->dir_next.x--;
	}
	if (event == IDisplay::Right) {
		this->dir_next.x++;
	}
}
