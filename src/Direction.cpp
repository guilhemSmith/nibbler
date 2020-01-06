/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Direction.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:25:45 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/04 18:02:31 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Direction.hpp"
#include <cstdlib>
#include <cmath>

Direction::Direction(int x, int y): x(x), y(y) {}
Direction::Direction(Direction const & rhs): x(rhs.x), y(rhs.y) {}
Direction::~Direction(void) {}

Direction const &	Direction::operator=(Direction const & rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

Direction const &	Direction::clamp(void) {
	int x = this->x;
	int y = this->y;
	int abs_x = abs(x);
	int abs_y = abs(y);
	
	if (abs_x > abs_y) {
		this->x = x / abs_x;
		this->y = 0;
	} else if (abs_x < abs_y) {
		this->x = 0;
		this->y = y / abs_y;
	} else {
		this->x = 0;
		this->y = 0;
	}
	return *this;
}

size_t				Direction::length(void) const {
	return static_cast<size_t>(sqrt(pow(this->x, 2) + pow(this->y, 2)));
}

bool				Direction::is_opposed_to(Direction const & rhs) const {
	return this->x == -rhs.x || this->y == -rhs.y;
}