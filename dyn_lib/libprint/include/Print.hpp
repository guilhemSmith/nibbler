/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Print.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:41:20 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/18 15:50:54 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_HPP
# define PRINT_HPP

# include <iostream>
# include "IDisplay.hpp"

class	PrintDisplay: public IDisplay {
public:
	PrintDisplay(void);
 	~PrintDisplay(void);
	void	displayGameWindow(void);
	void	sayHello(std::string name);
	void	eventLoop(void);
	void	swapDisplay(int newDisplay);

private:
	PrintDisplay(PrintDisplay const &src);
	PrintDisplay &operator=(PrintDisplay const &rhs);
};

extern "C" {
    IDisplay *createDisplay(void);
    void deleteDisplay(IDisplay *disp);
    void sayHello(std::string name);
    void eventLoop(void);
    void swapDisplay(int newDisplay);
}

#endif
