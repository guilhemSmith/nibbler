/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:47 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 15:46:55 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Apple.hpp"
#include "Snake.hpp"
#include "Obstacle.hpp"

Game::Game(size_t width, size_t height): stopped(false), paused(false), \
				 score(0), grid(Grid(width, height)){}

Game::~Game(void) {}

Game::Game(Game const & rhs): paused(rhs.paused), score(rhs.score), \
				grid(rhs.grid) {}

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

void			Game::print_grid(void) const {
	this->grid.print(this->display);
}

bool			Game::move(int x, int y) {
	return this->grid.move_head(x, y);
}

int				Game::get_score(void) const {
	return this->score;
}


void			Game::quit_game(void) {
	this->stopped = true;
}

bool			Game::run(void) const {
	if (this->stopped)
		return false;
	this->print_grid();
	return true;
}

void			Game::set_display(IDisplay *disp) {
	this->display = disp;
}
