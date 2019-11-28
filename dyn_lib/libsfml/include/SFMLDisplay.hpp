/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SFMLDisplay.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:20:13 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/28 15:32:39 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SFML_DISPLAY_HPP
# define SFML_DISPLAY_HPP

# include <iostream>
# include <SFML/Graphics.hpp>
# include <map>
# include "IDisplay.hpp"

# define WIDTH_CELL 30
# define HEIGHT_CELL 30

class	SFMLDisplay: public IDisplay {
public:
	SFMLDisplay(void);
 	~SFMLDisplay(void);

	void				newWindow(size_t x, size_t y);
	void				clearDisplay(void);
	void				refreshDisplay(void);
	void				drawStatic(t_position pos, EMotif motif);
	void				drawMobile(t_position start, t_position stop, \
							EMotif motif, int progression);
	void				drawScore(int score);
	EEvent 				pollEvent(void);

private:
	SFMLDisplay(SFMLDisplay const &src);
	SFMLDisplay 		&operator=(SFMLDisplay const &rhs);
	sf::RenderWindow	*_window;
	
	const static std::map<sf::Keyboard::Key, IDisplay::EEvent> keyboardToEvent;
};

extern "C" {
    IDisplay			*createDisplay(void);
    void				deleteDisplay(IDisplay *disp);
}

#endif
