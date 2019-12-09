/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/09 18:24:40 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Loader.hpp"
# include "Grid.hpp"
# include "Direction.hpp"

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
	bool				speedup;
	Direction			dir;
	Direction			dir_next;
	size_t				frame;
	size_t				frame_per_cell;
	Loader				loader;
	Grid				grid;
	
	void				update_dir(IDisplay::EEvent event);
	bool				spawn_obstacle(Position pos);
	bool				spawn_apple(Position pos);
	bool				spawn_snake(Position pos, Direction dir);

	static size_t const	disp_freq = 16666;
	static size_t const	max_speed = 3;
};

#endif
