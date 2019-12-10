/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Score.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 12:16:17 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 13:13:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Score.hpp"

Score::Score(void): value(0), speedup(false) {}

Score::~Score(void) {}

int		Score::increase_speed(void) {
	int		flag;

	flag = this->speedup;
	if (this->speedup > 0) {
		this->speedup = 0;
	}
	return flag;
}

int		Score::get_score(void) const {
	return this->value;
}

void	Score::increment_score(int amount) {
	if (amount >= Score::palier) {
		this->speedup += Score::palier / amount;
	}
	if (this->value % Score::palier + amount % Score::palier >= Score::palier) {
		this->speedup += 1;
	}
	this->value += amount;
}