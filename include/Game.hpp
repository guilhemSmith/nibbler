/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/04 18:05:36 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Loader.hpp"
# include "Grid.hpp"
# include "Direction.hpp"

# define SPEED_START 10

class Game {
public:
	Game(int lib, size_t width, size_t height);
	~Game(void);

	bool				run(void);

private:
	Game(void);
	Game const &		operator=(Game const & rhs) const;

	bool				paused;
	int					score;
	Direction			dir;
	Direction			dir_next;
	size_t				frame;
	size_t				speed;
	Loader				loader;
	Grid				grid;
	
	void				update_dir(IDisplay::EEvent event);
	bool				spawn_obstacle(size_t x, size_t y);
	bool				spawn_apple(size_t x, size_t y);
	bool				spawn_snake(size_t x, size_t y, int dir_x, int dir_y);

	static size_t const	disp_freq = 16666;
};

#endif
