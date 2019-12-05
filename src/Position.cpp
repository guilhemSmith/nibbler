/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Position.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:25:45 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 11:52:14 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Position.hpp"
#include <cstdlib>
#include <cmath>

Position::Position(size_t x, size_t y): x(x), y(y) {}
Position::Position(Position const & rhs): x(rhs.x), y(rhs.y) {}
Position::~Position(void) {}

Position const &	Position::operator=(Position const & rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

Position const &	Position::clamp(size_t width, size_t height) {
	if (this->x >= width) {
		if (this->x == width)
			this->x = 0;
		else
			this->x = width - 1;
	}
	if (this->y >= height) {
		if (this->y == height)
			this->y = 0;
		else
			this->y = height - 1;
	}
	return *this;
}

size_t				Position::to_index(size_t width) const {
	return this->x + this->y * width;
}