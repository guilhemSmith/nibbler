/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:52:56 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:00:01 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obstacle.hpp"

Obstacle::Obstacle(void) {}

Obstacle::Obstacle(Obstacle const & ) {}

Obstacle::~Obstacle(void) {}

IEntity *		Obstacle::clone(void) const {
	return new Obstacle(*this);
}

bool			Obstacle::is_collider(void) const {
	return true;
}

char			Obstacle::get_symbol(void) const {
	return '*';
}