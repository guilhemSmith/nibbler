/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursessDisplay.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:16:58 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/29 16:01:26 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_DISPLAY_HPP
# define NCURSES_DISPLAY_HPP

# include <iostream>
# include <ncurses.h>
# include <map>
# include "Symbol.hpp"
# include "IDisplay.hpp"


class	NcursesDisplay: public IDisplay {
public:
	NcursesDisplay(void);
 	~NcursesDisplay(void);

	void				newWindow(size_t x, size_t y);
	void				clearDisplay(void);
	void				refreshDisplay(void);
	void				drawStatic(Position & pos, EMotif motif);
	void				drawMobile(Position & pos, Direction & dest, \
							Direction & from, EMotif motif, float progression);
	void				drawScore(int score);
	EEvent 				pollEvent(void);

private:
	NcursesDisplay(NcursesDisplay const &src);
	NcursesDisplay 		&operator=(NcursesDisplay const &rhs);

	WINDOW				*_window;
	static void			initColors(void);
	const static std::map<IDisplay::EMotif, Symbol &> motifToSymbol;
	const static std::map<int, IDisplay::EEvent> keyboardToEvent;
};

extern "C" {
    IDisplay			*createDisplay(void);
    void				deleteDisplay(IDisplay *disp);
}

#endif
