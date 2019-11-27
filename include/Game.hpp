/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 16:50:08 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_HPP
# define GAME_HPP

# include "Grid.hpp"

class Game {
public:
	Game(size_t width, size_t height);
	Game(Game const & rhs);
	~Game(void);

	bool			spawn_obstacle(size_t x, size_t y);
	bool			spawn_apple(size_t x, size_t y);
	bool			spawn_snake(size_t x, size_t y, int dir_x, int dir_y);
	void			print_grid(void) const;
	bool			move(int x, int y);
	int				get_score(void) const;
	void			quit_game(void);
	void			set_display(IDisplay *disp);
	bool			run(void) const;

private:
	Game(void);
	Game const &	operator=(Game const & rhs) const;

	bool			stopped;
	bool			paused;
	int				score;
	IDisplay		*display;
	Grid			grid;
};

#endif
