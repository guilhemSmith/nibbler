/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Position.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:45:29 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 13:50:26 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Position.hpp"


Position::Position(size_t x, size_t y): x(x), y(y) {}

Position::Position(Position const & rhs): x(rhs.x), y(rhs.y) {}

Position::~Position(void) {}

Position const &	Position::operator=(Position const & rhs) {
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

size_t				Position::get_x(void) const {
	return this->x;
}

size_t				Position::get_y(void) const {
	return this->y;
}

void				Position::set_x(size_t x) {
	this->x = x;
}

void				Position::set_y(size_t y) {
	this->y = y;
}