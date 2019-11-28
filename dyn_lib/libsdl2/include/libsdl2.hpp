/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsdl2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:08:14 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/28 17:56:27 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL2_HPP
# define LIBSDL2_HPP

# include "DisplaySDL2.hpp" 

extern "C" {
	IDisplay *		createDisplay(void);
	void			deleteDisplay(IDisplay * display);
}

#endif