/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/28 17:37:01 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

#include "Loader.hpp"
# include "Grid.hpp"

class Game {
public:
	Game(int lib, size_t width, size_t height);
	~Game(void);

	bool			run(void);

private:
	Game(void);
	Game const &	operator=(Game const & rhs) const;

	bool			paused;
	int				score;
	Loader			loader;
	Grid			grid;
	
	bool			spawn_obstacle(size_t x, size_t y);
	bool			spawn_apple(size_t x, size_t y);
	bool			spawn_snake(size_t x, size_t y, int dir_x, int dir_y);
};

#endif
