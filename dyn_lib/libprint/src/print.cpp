/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:48:56 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/18 15:49:44 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Print.hpp"

void	sayHello(std::string name) {
	std::cout << "Hello, " << name << '!' << std::endl;
}

PrintDisplay::PrintDisplay(void) {
}

PrintDisplay::~PrintDisplay(void) {
}

void	PrintDisplay::displayGameWindow(void) {
    std::cout << "DisplayGameWindow called from PrintLib" << std::endl;
}

void	PrintDisplay::sayHello(std::string name) {
    std::cout << "This from Print Lib: hello, " << name << "!" << std::endl;
}

IDisplay *createDisplay(void) {
    return new PrintDisplay();
}

void	deleteDisplay(IDisplay *disp) {
    delete disp;
}

void	PrintDisplay::swapDisplay(int newDisplay) {
    std::cout << "must swap display to " << newDisplay << std::endl;
}

void	PrintDisplay::eventLoop(void) {
    while (1)
	;
}

