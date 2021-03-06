/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2020/01/07 15:51:57 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Loader.hpp"
# include "Grid.hpp"
# include "Direction.hpp"
# include "Score.hpp"

class Game {
public:
	Game(int lib, size_t width, size_t height);
	~Game(void);

	bool				run(void);

private:
	Game(void);
	Game const &		operator=(Game const & rhs) const;

	bool				paused;
	Score				score;
	Direction			dir;
	Direction			dir_next;
	Direction			dir_memorized;
	size_t				frame;
	size_t				frame_per_cell;
	Loader				loader;
	Grid				grid;
	Position			bonus_pos;
	int					bonus_timer;
	
	void				update_dir(IDisplay::EEvent event, Direction & dir);
	bool				spawn_obstacle(Position pos);
	bool				spawn_apple(Position pos);
	bool				spawn_snake(Position pos, Direction dir);
	void				handle_event(IDisplay::EEvent event, bool & stop, \
							IDisplay ** disp);
	void				handle_bonus(void);
	void				game_frame(bool & stop);
	void				game_over(void);

	static size_t const	disp_freq = 16666;
	static size_t const	max_speed = 3;
	static size_t const	start_speed = 10;
	static int const	bonus_freq = 75;
};

#endif
