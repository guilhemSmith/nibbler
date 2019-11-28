/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsdl2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:10:23 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/28 17:56:21 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl2.hpp"

IDisplay *	createDisplay(void) {
	return new DisplaySDL2();
}

void			deleteDisplay(IDisplay * display) {
	delete display;
}