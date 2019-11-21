/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:47 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:15:44 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"
#include "Apple.hpp"
#include "Obstacle.hpp"

Game::Game(size_t width, size_t height): paused(false), score(0), \
				grid(Grid(width, height)) {}

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
	Apple *	apl = new Apple();

	if (!this->grid.spawn(apl, x, y)) {
		delete apl;
		return false;
	}
	return true;
}

void			Game::print_grid(void) const {
	this->grid.print();
}