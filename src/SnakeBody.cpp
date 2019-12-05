/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeBody.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:54:42 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 17:21:02 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeBody.hpp"

SnakeBody::SnakeBody(Direction dir): dir(dir) {}

SnakeBody::SnakeBody(SnakeBody const & rhs): dir(rhs.dir) {}

SnakeBody::~SnakeBody(void) {}

IEntity *			SnakeBody::clone(void) const {
	return new SnakeBody(*this);
}

bool				SnakeBody::collide(void) {
	return true;
}

char				SnakeBody::get_symbol(void) const {
	return 'o';
}

Direction			SnakeBody::get_dir(void) const {
	return this->dir;
}

void				SnakeBody::set_dir(Direction dir) {
	this->dir = dir;
}

Position			SnakeBody::get_dest(Position pos) const {
	return Position(pos.x + this->dir.x, pos.y + this->dir.y); 
}

IDisplay::EMotif	SnakeBody::get_motif(void) const {
	return IDisplay::snake;
}

bool				SnakeBody::is_mobile(void) const {
	return true;
}