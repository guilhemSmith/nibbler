/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libglfw.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 13:08:14 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/27 11:06:22 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGLFW_HPP
# define LIBGLFW_HPP

# include "DisplayGLFW.hpp" 

extern "C" {
	IDisplay *		createDisplay(void);
	void			deleteDisplay(IDisplay * display);
}

#endif