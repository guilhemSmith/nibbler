/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:22 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 18:09:59 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYSDL2_HPP
# define DISPLAYSDL2_HPP

# include <exception>
# include <string>
# include <SDL2/SDL.h>
# include "IDisplay.hpp"

class DisplaySDL2: IDisplay {
public:
	class SDL2Except: std::exception {
	public:
		SDL2Except(std::string message);
		SDL2Except(SDL2Except const & rhs);
		~SDL2Except(void);

		char const *		what(void) const throw();

	private:
		SDL2Except(void);
		SDL2Except const &	operator=(SDL2Except const & rhs);

		std::string			message;
	};
	DisplaySDL2(void);
	DisplaySDL2(DisplaySDL2 const & rhs);
	~DisplaySDL2(void);

	DisplaySDL2 const &	operator=(DisplaySDL2 const & rhs);

	void				newWindow(size_t x, size_t y);
	void				refreshDisplay(void);
	void				drawStatic(t_position pos, EMotif motif);
	void				drawMobile(t_position start, t_position stop, \
							EMotif color, int progression);
	void				drawScore(int score);
	EEvent 				pollEvent(void);
private:
	size_t				width;
	size_t				height;
	SDL_Window *		window;

	static size_t const	cell_size = 30; 
};

#endif