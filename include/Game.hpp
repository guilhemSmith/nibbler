/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 15:44:26 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Loader.hpp"
# include "Grid.hpp"
# include "Direction.hpp"

# define SPEED_START 5

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
	bool				spawn_obstacle(Position pos);
	bool				spawn_apple(Position pos);
	bool				spawn_snake(Position pos, Direction dir);

	static size_t const	disp_freq = 16666;
};

#endif
