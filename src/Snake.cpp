/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:54:42 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 13:34:16 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Snake.hpp"

Snake::Snake(int x, int y): dir({x, y}) {}

Snake::Snake(Snake const & rhs): dir({rhs.dir[0], rhs.dir[1]}) {}

Snake::~Snake(void) {}

IEntity *			Snake::clone(void) const {
	return new Snake(*this);
}

bool				Snake::collide(void) {
	return true;
}

char				Snake::get_symbol(void) const {
	return 'o';
}

std::array<int, 2>	Snake::get_dir(void) const {
	return this->dir;
}

void				Snake::set_dir(int x, int y) {
	this->dir[0] = x;
	this->dir[1] = y;
}