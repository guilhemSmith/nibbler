/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:27:47 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/21 18:03:36 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FSMLDisplay.hpp"

FSMLDisplay::FSMLDisplay(void) {
	
}

FSMLDisplay::~FSMLDisplay(void) {
	delete _window;
}

sf::RenderWindow	*FSMLDisplay::getWindow() const {
	return	_window;
}
