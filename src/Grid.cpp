/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:51:59 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:08:20 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "Grid.hpp"

Grid::Grid(size_t width, size_t height): width(width), height(height), \
				entities(std::vector<IEntity *>(width * height)) {}

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