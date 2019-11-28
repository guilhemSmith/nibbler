/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:52:56 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 16:51:21 by tbehra           ###   ########.fr       */
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
