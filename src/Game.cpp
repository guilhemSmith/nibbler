/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:47 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/09 18:25:00 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ctime>
#include <iostream>
#include "Game.hpp"
#include "Apple.hpp"
#include "SnakeBody.hpp"
#include "Obstacle.hpp"

Game::Game(int lib, size_t width, size_t height): \
				paused(false), score(0), speedup(false), dir(Direction(0, 1)), \
				dir_next(Direction(0, 0)), frame(0), frame_per_cell(15), \
				loader(lib, width, height), grid(Grid(width, height)) {
	for (size_t i = 0; i < width; i++) {
		this->spawn_obstacle(Position(i, 0));
		this->spawn_obstacle(Position(i, height - 1));
	}

	this->spawn_obstacle(Position(width / 3, height / 2));
	this->spawn_apple(Position(width / 2 + 7, height / 2));
}

Game::~Game(void) {}

bool			Game::spawn_obstacle(Position pos) {
	Obstacle *	obs = new Obstacle();

	if (!this->grid.spawn(obs, pos)) {
		delete obs;
		return false;
	}
	return true;
}

bool			Game::spawn_apple(Position pos) {
	Apple *	apl = new Apple(this->score, this->speedup);

	if (!this->grid.spawn(apl, pos)) {
		delete apl;
		return false;
	}
	return true;
}

bool			Game::spawn_snake(Position pos, Direction dir) {
	SnakeBody *	snk = new SnakeBody(dir);

	if (!this->grid.spawn(snk, pos)) {
		delete snk;
		return false;
	}
	return true;
}

bool			Game::run(void) {
	IDisplay::EEvent	event;
	IDisplay *			disp = this->loader.get_display();
	size_t				time_start = time(0);
	bool				stop = false;
	float				adv;

	while ((event = disp->pollEvent()) != IDisplay::None) {
		if (event == IDisplay::Quit) {
			stop = true;
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
	if (this->frame == this->frame_per_cell) {
		this->dir_next.clamp();
		if (!this->grid.move_head(this->dir)) {
			stop = true;
		}
		if (this->dir_next.length() != 0) {
			if (!this->dir.is_opposed_to(this->dir_next)) {
				this->dir = this->dir_next;
			}
			this->dir_next = Direction(0, 0);
		}
		this->grid.set_head_dir(this->dir);
		this->frame = 0;
		if (this->speedup && this->frame_per_cell > Game::max_speed) {
			this->frame_per_cell--;
			this->speedup = false;
		}
	}
	if (stop) {
		return false;
	}
	adv = static_cast<float>(frame) / static_cast<float>(this->frame_per_cell);
	usleep(Game::disp_freq - (time(0) - time_start));
	this->grid.print(this->loader.get_display(), adv);
	disp->drawScore(this->score);
	disp->refreshDisplay();
	return !stop;
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
