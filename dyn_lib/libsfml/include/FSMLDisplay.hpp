/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:20:13 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/21 18:03:17 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSML_DISPLAY_HPP
# define FSML_DISPLAY_HPP

# include <iostream>
# include <SFML/Graphics.hpp>
# include "IDisplay.hpp"

class	FSMLDisplay: public IDisplay {
public:
	FSMLDisplay(void);
 	~FSMLDisplay(void);
	sf::RenderWindow	*getWindow(void) const;
	void			displayGameWindow(void);
	void			sayHello(std::string name);

private:
				FSMLDisplay(FSMLDisplay const &src);
	FSMLDisplay 		&operator=(FSMLDisplay const &rhs);
	sf::RenderWindow	*_window;
};

extern "C" {
    IDisplay *createDisplay(void);
    void deleteDisplay(IDisplay *disp);
    void sayHello(std::string name);
}

#endif
