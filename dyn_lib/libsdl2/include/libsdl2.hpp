/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libsdl2.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:08:14 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 14:34:46 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSDL2_HPP
# define LIBSDL2_HPP

# include "DisplaySDL2.hpp" 

extern "C" {
	DisplaySDL2 *	createDisplaySDL2(void);
	void			deleteDisplaySDL2(DisplaySDL2 * display);
}

#endif