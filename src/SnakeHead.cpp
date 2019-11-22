/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeHead.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:01:05 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 11:44:02 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeHead.hpp"

SnakeHead::SnakeHead(int x, int y, int tail_x, int tail_y): Snake(x, y), \
					tail({tail_x, tail_y}) {}

SnakeHead::SnakeHead(SnakeHead const & rhs): Snake(rhs), tail(rhs.tail) {}

SnakeHead::~SnakeHead(void) {}

IEntity *			SnakeHead::clone(void) const {
	return new SnakeHead(*this);
}

char				SnakeHead::get_symbol(void) const {
	return 'X';
}

std::array<int, 2>	SnakeHead::get_tail(void) const {
	return this->tail;
}

void				SnakeHead::forward_tail(int x, int y) {
	this->tail[0] = x + this->tail[0];
	this->tail[1] = y + this->tail[1];
}