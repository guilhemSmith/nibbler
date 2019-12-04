/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Symbol.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:37:55 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/29 14:36:30 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Symbol.hpp"

Symbol::Symbol(char sym, Symbol::color col): _sym(sym), _color(col) {

}

Symbol::~Symbol(void) {
}

Symbol::color	Symbol::get_color(void) {
	return this->_color;
}

char	Symbol::get_sym(void) {
	return this->_sym;
}
