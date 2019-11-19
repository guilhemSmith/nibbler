/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Arguments.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:05:48 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/19 17:07:59 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <sstream>
#include <iostream>
#include "Arguments.hpp"

Arguments::Arguments(int argc, char * argv[]) {
	if (argc != 4) {
		throw Arguments::InvalidArguments();
	}
	this->initStartingLib(argv[1]);
	this->initWidth(argv[2]);
	this->initHeight(argv[3]);
}

Arguments::~Arguments(void) {}

int				Arguments::getStartingLib(void) {
	return this->startingLib;
}
int				Arguments::getWidth(void) {
	return this->width;
}
int				Arguments::getHeight(void) {
	return this->height;
}

void			Arguments::initStartingLib(char * arg) {
	int		val;

	try {
		val = std::stoi(arg);
	} catch (std::exception unexpected) {
		throw Arguments::InvalidArguments();
	}
	if (val > STARTINGLIB_MAX || val < STARTINGLIB_MIN) {
		throw Arguments::InvalidArguments();
	}
	this->startingLib = val;
}

void			Arguments::initWidth(char * arg) {
	int		val;

	try {
		val = std::stoi(arg);
	} catch (std::exception unexpected) {
		throw Arguments::InvalidArguments();
	}
	if (val > WIDTH_MAX || val < WIDTH_MIN) {
		throw Arguments::InvalidArguments();
	}
	this->width = val;
}

void			Arguments::initHeight(char * arg) {
	int		val;

	try {
		val = std::stoi(arg);
	} catch (std::exception unexpected) {
		throw Arguments::InvalidArguments();
	}
	if (val > HEIGHT_MAX || val < HEIGHT_MIN) {
		throw Arguments::InvalidArguments();
	}
	this->height = val;
}

Arguments::InvalidArguments::InvalidArguments(void) {
	std::stringstream		sstr;

	sstr << "usage: ./nibbler lib width height" \
		<< "\n\tlib: Number of the lib used on start, should be between " \
		<< STARTINGLIB_MIN << " and " << STARTINGLIB_MAX << "." \
		<< "\n\t     This number can be changed while the program is running" \
		<< " with the numkeys." \
		<< "\n\twidth: The width of the window, should be between " \
		<< WIDTH_MIN << " and " << WIDTH_MAX << "." \
		<< "\n\theight: The height of the window, should be between " \
		<< HEIGHT_MIN << " and " << HEIGHT_MAX << ".";
	this->usage = sstr.str();
}

Arguments::InvalidArguments::InvalidArguments(InvalidArguments const & rhs): \
				usage(rhs.usage) {}

Arguments::InvalidArguments::~InvalidArguments(void) {}

char const *	Arguments::InvalidArguments::what(void) const throw() {
	return this->usage.c_str();
}