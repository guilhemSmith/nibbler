/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeHead.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:01:05 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/25 16:41:55 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeHead.hpp"

SnakeHead::SnakeHead(int x, int y, size_t tail_x, size_t tail_y): Snake(x, y), \
						tail({tail_x, tail_y}) {}

SnakeHead::SnakeHead(SnakeHead const & rhs): Snake(rhs), tail(rhs.tail) {}

SnakeHead::~SnakeHead(void) {}

IEntity *				SnakeHead::clone(void) const {
	return new SnakeHead(*this);
}

char					SnakeHead::get_symbol(void) const {
	return 'X';
}

std::array<size_t, 2>	SnakeHead::get_tail(void) const {
	return this->tail;
}



void					SnakeHead::set_tail(std::array<size_t, 2> pos) {
	this->tail = pos;
}