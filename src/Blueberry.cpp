/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Blueberry.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:21:34 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 18:07:46 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Blueberry.hpp"

Blueberry::Blueberry(Score & score): Apple(score), value(Blueberry::new_val) {}
Blueberry::Blueberry(Blueberry const & rhs): Apple(rhs), value(rhs.value) {}
Blueberry::~Blueberry(void) {}

char				Blueberry::get_symbol(void) const {
	return 'B';
}

bool				Blueberry::collide(void) {
	this->score.increment_score(this->value);
	return false;
}

IDisplay::EMotif	Blueberry::get_motif(void) const {
	return IDisplay::blueberry;
}

size_t				Blueberry::grow_value(void) const {
	return 3;
}

bool				Blueberry::rot(void) {
	if (this->value < 3) {
		return true;
	}
	this->value -= 3;
	return false;
}