/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:47 by gsmith            #+#    #+#             */
/*   Updated: 2020/03/05 13:48:46 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ctime>
#include <iostream>
#include "Game.hpp"
#include "Apple.hpp"
#include "SnakeBody.hpp"
#include "Obstacle.hpp"
#include "Blueberry.hpp"

Game::Game(int lib, size_t width, size_t height): \
				paused(false), score(), dir(Direction(0, 1)), \
				dir_next(Direction(0, 0)), dir_memorized(Direction(0, 0)), \
				frame(0), frame_per_cell(Game::start_speed), \
				loader(lib, width, height), grid(Grid(width, height)), \
				bonus_pos(0, 0), bonus_timer(Game::bonus_freq) {
	for (size_t i = 0; i < width; i++) {
		if (i < width / 3 || i >= 2 * width / 3) {
			this->spawn_obstacle(Position(i, 0));
			this->spawn_obstacle(Position(i, height - 1));
		}
	}
	for (size_t i = 0; i < height; i++) {
		if (i < height / 3 || i >= 2 * height / 3) {
			this->spawn_obstacle(Position(0, i));
			this->spawn_obstacle(Position(width - 1, i));
		}
	}
	while (!this->spawn_apple(Position(rand() % width, rand() % height)));
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
	Apple *	apl = new Apple(this->score);

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
		this->handle_event(event, stop, &disp);
	}
	this->frame += 1;
	if (this->frame == this->frame_per_cell) {
		this->game_frame(stop);
		this->handle_bonus();
	}
	if (stop) {
		this->game_over();
		return false;
	}
	adv = static_cast<float>(frame) / static_cast<float>(this->frame_per_cell);
	usleep(Game::disp_freq - (time(0) - time_start));
	this->grid.print(this->loader.get_display(), adv);
	disp->drawScore(this->score.get_score());
	disp->refreshDisplay();
	return !stop;
}

void			Game::game_frame(bool & stop) {
	this->frame_per_cell -= this->score.increase_speed();
	if (this->frame_per_cell < Game::max_speed) {
		this->frame_per_cell = Game::max_speed;
	}
	this->dir_next.clamp();
	if (!this->grid.move_head(this->dir)) {
		stop = true;
	}
	if (this->dir_next.length() != 0) {
		if (!this->dir.is_opposed_to(this->dir_next)) {
			this->dir = this->dir_next;
		}
		this->dir_next = this->dir_memorized;
		this->dir_memorized = Direction(0, 0);
	}
	this->grid.set_head_dir(this->dir);
	this->frame = 0;
}

void			Game::handle_event(IDisplay::EEvent event, bool & stop, \
					IDisplay ** disp) {
	if (event == IDisplay::Quit) {
		stop = true;
	}
	if (event >= IDisplay::Up && event <= IDisplay::Right) {
		if (this->dir_next.length() == 0)
			this->update_dir(event, this->dir_next);
		else
			this->update_dir(event, this->dir_memorized);
	}
	if (event >= IDisplay::One && event <= IDisplay::Three) {
		try {
			this->loader.load_lib(event - IDisplay::One + 1, \
				this->grid.get_width(), this->grid.get_height());
		} catch (std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
		*disp = this->loader.get_display();
	}
}

void			Game::handle_bonus(void) {
	this->bonus_timer--;
	if (this->bonus_timer == 0 || this->grid.rot_berry(this->bonus_pos)) {
		Blueberry *	berry = new Blueberry(this->score);
		this->bonus_pos = Position(rand() % this->grid.get_width(), \
			rand() %this->grid.get_height());
		if (!this->grid.spawn(berry, this->bonus_pos)) {
			delete berry;
			this->bonus_timer = 1;
		}
		this->bonus_timer = Game::bonus_freq;
	}
}

void			Game::update_dir(IDisplay::EEvent event, Direction & dir) {
	if (event == IDisplay::Up) {
		dir.y--;
	}
	if (event == IDisplay::Down) {
		dir.y++;
	}
	if (event == IDisplay::Left) {
		dir.x--;
	}
	if (event == IDisplay::Right) {
		dir.x++;
	}
}

void			Game::game_over(void) {
	IDisplay *			disp = this->loader.get_display();
	size_t				time_start;
	int					i = 0;
	int					frame_wait = 10;
	
	while (i++ < frame_wait) {
		time_start = time(0);
		while (disp->pollEvent() != IDisplay::None);
		usleep(Game::disp_freq - (time(0) - time_start));
	}
	std::cout << "Score: " << this->score.get_score() << std::endl;
}