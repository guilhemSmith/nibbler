/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:52:56 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:01:08 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Apple.hpp"

Apple::Apple(void) {}

Apple::Apple(Apple const & ) {}

Apple::~Apple(void) {}

IEntity *		Apple::clone(void) const {
	return new Apple(*this);
}

bool			Apple::is_collider(void) const {
	return false;
}

char			Apple::get_symbol(void) const {
	return '@';
}