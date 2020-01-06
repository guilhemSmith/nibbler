/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeHead.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 11:01:05 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 13:16:19 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeHead.hpp"

SnakeHead::SnakeHead(Direction dir, Position tail_pos): \
						SnakeBody(dir), tail(tail_pos) {}

SnakeHead::SnakeHead(SnakeHead const & rhs): SnakeBody(rhs), tail(rhs.tail) {}

SnakeHead::~SnakeHead(void) {}

IEntity *				SnakeHead::clone(void) const {
	return new SnakeHead(*this);
}

char					SnakeHead::get_symbol(void) const {
	return 'X';
}

Position	SnakeHead::get_tail(void) const {
	return this->tail;
}

void					SnakeHead::set_tail(Position pos) {
	this->tail = pos;
}

IDisplay::EMotif		SnakeHead::get_motif(void) const {
	return IDisplay::snakeHead;
}
