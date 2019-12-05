/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:52:56 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 16:23:38 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Apple.hpp"

int const		Apple::value = 50;

Apple::Apple(int & score, bool & speedup): score(score), speedup(speedup) {}

Apple::Apple(Apple const & rhs): score(rhs.score), speedup(rhs.speedup) {}

Apple::~Apple(void) {}

IEntity *				Apple::clone(void) const {
	return new Apple(*this);
}

bool					Apple::collide(void) {
	this->increment_score();
	return false;
}

char					Apple::get_symbol(void) const {
	return '@';
}

void					Apple::increment_score(void) {
	this->score += Apple::value;
	this->speedup = true;
}

IDisplay::EMotif		Apple::get_motif(void) const {
	return IDisplay::apple;
}

size_t				Apple::grow_value(void) const {
	return 1;
}