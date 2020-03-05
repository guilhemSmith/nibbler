/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libglfw.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:10:23 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/27 11:06:56 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libglfw.hpp"

IDisplay *	createDisplay(void) {
	return new DisplayGLFW();
}

void			deleteDisplay(IDisplay * display) {
	delete display;
}