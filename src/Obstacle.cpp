/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:52:56 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 17:21:52 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Obstacle.hpp"

Obstacle::Obstacle(void) {}

Obstacle::Obstacle(Obstacle const & ) {}

Obstacle::~Obstacle(void) {}

IEntity *		Obstacle::clone(void) const {
	return new Obstacle(*this);
}

bool			Obstacle::collide(void) {
	return true;
}

char			Obstacle::get_symbol(void) const {
	return '*';
}

IDisplay::EMotif	Obstacle::get_motif(void) const {
	return IDisplay::obstacle;
}

bool				Obstacle::is_mobile(void) const {
	return false;
}