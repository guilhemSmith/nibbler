/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsdl2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:10:23 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 14:34:55 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl2.hpp"

DisplaySDL2 *	createDisplaySDL2(void) {
	return new DisplaySDL2();
}

void			deleteDisplaySDL2(DisplaySDL2 * display) {
	delete display;
}