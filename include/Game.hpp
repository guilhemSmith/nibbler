/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:39:36 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:15:15 by gsmith           ###   ########.fr       */
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
	void			print_grid(void) const;

private:
	Game(void);
	Game const &	operator=(Game const & rhs) const;

	bool			paused;
	int				score;
	Grid			grid;
};

#endif