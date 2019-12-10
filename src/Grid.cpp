/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:51:59 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 17:02:19 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Grid.hpp"
#include "SnakeTail.hpp"
#include "Apple.hpp"
#include "Blueberry.hpp"

#include <iostream>
#include <cstdlib>

Grid::Grid(size_t width, size_t height): \
				width(width), height(height), grow(false), grow_val(0), \
				entities(std::vector<IEntity *>(width * height)), \
				head_pos(width / 2, height / 2), head(NULL) {
	this->head = new SnakeHead(Direction(0, 1), \
		Position(this->head_pos.x, head_pos.y - 4));
	this->entities[this->head_pos.to_index(width)] = this->head;
	for (int i = 1; i < 4; i++) {
		Position pos(this->head_pos);
		pos.y -= i;
		this->entities[pos.to_index(width)] = new SnakeBody(Direction(0, 1));
	}
	Position pos(this->head_pos);
	pos.y -= 4;
	this->entities[pos.to_index(width)] = new SnakeTail(Direction(0, 1));
	srand (time(0));
}

Grid::Grid(Grid const & rhs): width(rhs.width), height(rhs.height), \
				entities(std::vector<IEntity *>(rhs.entities.size())), \
				head_pos(rhs.head_pos) {
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

bool			Grid::spawn(IEntity *entity, Position pos) {
	pos.clamp(this->width, this->height);
	size_t index = pos.to_index(this->width);
	if (this->entities[index] == NULL) {
		this->entities[index] = entity;
		return true;
	}
	return false;
}

void			Grid::print(IDisplay *disp, float adv) const {

	if (disp) {
		disp->clearDisplay();
		for (size_t i = 0; i < this->entities.size(); i++) {
			IEntity *	entity = this->entities[i];
			if (entity != NULL && !entity->is_mobile())
			{
				Position  pos(i % this->width, i / this->width);
				try {
					disp->drawStatic(pos, entity->get_motif());
				} catch (std::exception & e) {
					std::cerr << e.what() << std::endl;
				}
			}
		}
		Position	pos = this->head_pos;
		Direction	dir = this->head->get_dir();
		disp->drawMobile(pos, dir, dir, head->get_motif(), adv);
		pos = this->head->get_tail();
		SnakeBody *	snk = dynamic_cast<SnakeBody *> \
			(this->entities[pos.to_index(this->width)]);
		dir = snk->get_dir();
		disp->drawMobile(pos, dir, dir, snk->get_motif(), adv);
		while (snk != this->head) {
			pos = snk->get_dest(pos);
			pos.clamp(this->width, this->height);
			snk = dynamic_cast<SnakeBody *> \
				(this->entities[pos.to_index(this->width)]);
			Direction dst = snk->get_dir();
			disp->drawMobile(pos, dst, dir, snk->get_motif(), adv);
			dir = dst;
		}
	}
}

bool			Grid::move_head(Direction dir) {
	Position	collid_pos(this->head_pos.x + dir.x, this->head_pos.y + dir.y);
	collid_pos.clamp(this->width, this->height);
	IEntity *	collider = this->entities[collid_pos.to_index(this->width)];
	bool		alive = true;

	if (collider != NULL) {
		if (collider->collide()) {
			alive = false;
		} else {
			alive = this->eat(collider);
		}
	}
	if (!this->grow) {
		this->updateTail(dir);
	} else {
		this->growSnake(dir);
	}
	if (alive) {
		this->updateHead(dir);
	}
	if (this->grow_val > 0) {
		this->grow = true;
	}
	return alive;
}

bool			Grid::eat(IEntity * collider) {
	if (this->eat_berry(collider)) {
		return true;
	}
	
	Apple *		apl = dynamic_cast<Apple *>(collider);
	if (apl == NULL) {
		return !this->grow;
	}
	this->grow_val += apl->grow_value();
	size_t		new_index = rand() % (this->width * this->height);
	size_t		i = 0;
	while (this->entities[new_index]) {
		new_index = (new_index + 1) % (this->width * this->height);
		i++;
		if (i == this->width * this->height) {
			return false;
		}
	}
	this->entities[new_index] = apl;
	return true;
}

bool			Grid::eat_berry(IEntity * collider) {
	Blueberry *	berry = dynamic_cast<Blueberry *>(collider);

	if (berry != NULL) {
		this->grow_val += berry->grow_value();
		delete berry;
		return true;
	}
	return false;
}

void			Grid::growSnake(Direction dir) {
	this->head_pos.clamp(this->width, this->height);
	this->entities[this->head_pos.to_index(this->width)] = new SnakeBody(dir);
	this->grow_val--;
	if (this->grow_val == 0) {
		this->grow = false;
	}
}

void			Grid::updateTail(Direction dir) {
	Position	tail_pos = this->head->get_tail();
	SnakeTail *	tail = dynamic_cast<SnakeTail *> \
		(this->entities[tail_pos.to_index(this->width)]);
	Position	new_pos = tail->get_dest(tail_pos);
	SnakeBody *	body;

	new_pos.clamp(this->width, this->height);
	body = dynamic_cast<SnakeBody *> \
		(this->entities[new_pos.to_index(this->width)]);
	this->head->set_tail(new_pos);
	tail->set_dir(body->get_dir());
	body->set_dir(dir);
	this->entities[this->head_pos.to_index(this->width)] = body;
	this->entities[new_pos.to_index(this->width)] = tail;
	this->entities[tail_pos.to_index(this->width)] = NULL;
}

void			Grid::updateHead(Direction dir) {
	this->head_pos.x = this->head_pos.x + dir.x;
	this->head_pos.y = this->head_pos.y + dir.y;
	this->head_pos.clamp(this->width, this->height);
	this->entities[this->head_pos.to_index(this->width)] = this->head;
}

size_t			Grid::get_width(void) const {
	return this->width;
}

size_t			Grid::get_height(void) const {
	return this->height;
}

void			Grid::set_head_dir(Direction dir) const {
	this->head->set_dir(dir);
}

bool			Grid::rot_berry(Position pos) {
	Blueberry *	berry;
	size_t		index = pos.to_index(this->width);
	
	berry = dynamic_cast<Blueberry*>(this->entities[index]);
	if (berry == NULL) {
		return true;
	}
	if (berry->rot()) {
		delete berry;
		this->entities[index] = NULL;
		return true;
	}
	return false;
}