/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:20:13 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/27 17:26:11 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSML_DISPLAY_HPP
# define FSML_DISPLAY_HPP

# include <iostream>
# include <SFML/Graphics.hpp>
# include "IDisplay.hpp"

# define WIDTH_CELL 50
# define HEIGHT_CELL 50

class	FSMLDisplay: public IDisplay {
public:
	FSMLDisplay(void);
 	~FSMLDisplay(void);

	void				newWindow(size_t x, size_t y);
	void				refreshDisplay(void);
	void				drawStatic(t_position pos, EMotif motif);
	void				drawMobile(t_position start, t_position stop, \
							EMotif motif, int progression);
	void				drawScore(int score);
	EEvent 				pollEvent(void);

private:
	FSMLDisplay(FSMLDisplay const &src);
	FSMLDisplay 		&operator=(FSMLDisplay const &rhs);
	sf::RenderWindow	*_window;
};

extern "C" {
    IDisplay			*createDisplay(void);
    void				deleteDisplay(IDisplay *disp);
}

#endif
