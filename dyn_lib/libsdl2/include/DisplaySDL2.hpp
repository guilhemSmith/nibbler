/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplaySDL2.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:22 by gsmith            #+#    #+#             */
/*   Updated: 2020/03/04 13:33:39 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYSDL2_HPP
# define DISPLAYSDL2_HPP

# include <exception>
# include <string>
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <map>
# include "IDisplay.hpp"

class DisplaySDL2: public IDisplay {
public:
	class SDL2Except: public std::exception {
	public:
		SDL2Except(std::string message);
		SDL2Except(SDL2Except const & rhs);
		~SDL2Except(void);

		virtual char const *	what(void) const throw();

	private:
		SDL2Except(void);
		SDL2Except const &		operator=(SDL2Except const & rhs);

		std::string				message;
	};
	DisplaySDL2(void);
	~DisplaySDL2(void);


	void						newWindow(size_t x, size_t y);
	void						clearDisplay(void);
	void						refreshDisplay(void);
	void						drawStatic(Position & pos, EMotif motif);
	void						drawMobile(Position & pos, Direction & dest, \
									Direction & from, \
									EMotif motif, float progression);
	void						drawScore(int score);
	EEvent 						pollEvent(void);
private:
	DisplaySDL2(DisplaySDL2 const & rhs);
	DisplaySDL2 const &			operator=(DisplaySDL2 const & rhs);
	
	size_t						width;
	size_t						height;
	SDL_Window *				wind;
	SDL_Surface *				surf;
	std::map<EMotif, Uint32>	motifMap;
	TTF_Font *					font;
	SDL_Rect					score_pos;

	EEvent						pollWindowEvent(SDL_Event event);
	EEvent						pollKeyDownEvent(SDL_Event event);

	static size_t const							cell_size = 32;
	static std::map<SDL_Scancode, EEvent> const keyMap;
};

#endif