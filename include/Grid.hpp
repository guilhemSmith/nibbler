/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:52:10 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 15:47:25 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_HPP
# define GRID_HPP

# include <vector>
# include <array>
# include "IEntity.hpp"
# include "SnakeHead.hpp"

class Grid {
public:
	Grid(size_t width, size_t height);
	Grid(Grid const & rhs);
	~Grid(void);

	bool					spawn(IEntity *entity, size_t x, size_t y);
	void					print(IDisplay *disp) const;
	bool					move_head(int x, int y);

private:
	Grid(void);
	Grid const &			operator=(Grid const & rhs) const;
	
	void					growSnake(int x, int y);
	void					updateTail(int x, int y);
	void					updateHead(int x, int y);
	size_t					clampPos(size_t &x, size_t &y) const;

	size_t					width;
	size_t					height;
	std::vector<IEntity *>	entities;
	std::array<size_t, 2>	head_pos;
	SnakeHead *				head;
	
};

#endif
