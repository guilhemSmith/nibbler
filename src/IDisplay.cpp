/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDisplay.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:16:11 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 16:21:19 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IDisplay.hpp"

IDisplay::DisplayExcept::DisplayExcept(void): message("") {}

IDisplay::DisplayExcept::DisplayExcept(DisplayExcept const & rhs): \
					message(rhs.message) {}

IDisplay::DisplayExcept::~DisplayExcept(void) {}

const char *	IDisplay::DisplayExcept::what(void) const throw() {
	return this->message.c_str();
}