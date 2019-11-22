/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:51:59 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 13:43:56 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Grid.hpp"

#include <iostream>

Grid::Grid(size_t width, size_t height): width(width), height(height), \
				entities(std::vector<IEntity *>(width * height)), \
				head_pos({0, 0}), head(NULL) {
	int		x = width / 2;
	int		y = height / 2;
	
	this->head_pos[0] = x;
	this->head_pos[1] = y;
	this->head = new SnakeHead(0, -1, x, y - 4);
	this->entities[x + width * y] = this->head;
	for (int i = 1; i < 5; i++) {
		this->entities[(y - i) * width + x] = new Snake(0, 1);
	}
}

Grid::Grid(Grid const & rhs): width(rhs.width), height(rhs.height), \
				entities(std::vector<IEntity *>(rhs.entities.size())) {
	for (size_t i = 0; i < rhs.entities.size(); i++) {
		if (rhs.entities[i] != NULL) {
			this->entities[i] = rhs.entities[i]->clone();
		}
	}
}

Grid::~Grid(void) {
	for (size_t i = 0; i < this->entities.size(); i++) {
		delete this->entities[i];
		this->entities[i] = NULL;
	}
	this->head = NULL;
}

bool			Grid::spawn(IEntity *entity, size_t x, size_t y) {
	size_t		pos;

	if (x >= this->width || y >= this->height) {
		return false;
	}
	pos = y * this->width + x;
	if (this->entities[pos] == NULL) {
		this->entities[pos] = entity;
		return true;
	}
	return false;
}

void			Grid::print(void) const {
	for (size_t i = 0; i < this->entities.size(); i++) {
		IEntity *	entity = this->entities[i];
		if (i % this->width == 0) {
			std::cout << '\n';
		}
		if (entity == NULL) {
			std::cout << ' ';
		} else {
			std::cout << entity->get_symbol();
		}
	}
	std::cout << std::endl;
}

bool			Grid::move_head(int x, int y) {
	std::array<int, 2>	tail_pos = this->head->get_tail();
	Snake *				tail = dynamic_cast<Snake *>( \
							this->entities[tail_pos[1] * this->width \
								+ tail_pos[0]]);
	std::array<int, 2>	tail_dir = tail->get_dir();

	this->head->forward_tail(tail_dir[0], tail_dir[1]);
	tail->set_dir(x, y);
	this->entities[this->head_pos[0] + this->head_pos[1] * this->width] = tail;
	this->entities[tail_pos[0] + tail_pos[1] * this->width] = NULL;
	this->head_pos[0] = this->head_pos[0] + x;
	this->head_pos[1] = this->head_pos[1] + y;
	IEntity *			collider = this->entities[this->head_pos[0] \
							+ this->head_pos[1] * this->width];
	if (collider != NULL && collider->collide()) {
		delete this->head;
		this->head = NULL;
		return false;
	}
	this->entities[this->head_pos[0] + this->head_pos[1] \
		* this->width] = this->head;
	return true;
}