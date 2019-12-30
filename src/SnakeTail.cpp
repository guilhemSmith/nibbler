/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeTail.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 11:30:33 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 13:21:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SnakeTail.hpp"

SnakeTail::SnakeTail(Direction dir): SnakeBody(dir) {}

SnakeTail::SnakeTail(SnakeTail const & rhs): SnakeBody(rhs) {}

SnakeTail::~SnakeTail(void) {}

bool					SnakeTail::collide(void) {
	return false;
}