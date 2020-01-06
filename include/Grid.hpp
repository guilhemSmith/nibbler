/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:52:10 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 16:06:30 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_HPP
# define GRID_HPP

# include <vector>
# include "IEntity.hpp"
# include "SnakeHead.hpp"
# include "Direction.hpp"

class Grid {
public:
	Grid(size_t width, size_t height);
	Grid(Grid const & rhs);
	~Grid(void);

	bool					spawn(IEntity *entity, Position pos);
	void					print(IDisplay *disp, float adv) const;
	bool					move_head(Direction dir);
	size_t					get_width(void) const;
	size_t					get_height(void) const;
	void					set_head_dir(Direction dir) const;
	bool					rot_berry(Position pos);

private:
	Grid(void);
	Grid const &			operator=(Grid const & rhs) const;
	
	bool					eat(IEntity * collider);
	bool					eat_berry(IEntity * collider);
	void					growSnake(Direction dir);
	void					updateTail(Direction dir);
	void					updateHead(Direction dir);

	size_t					width;
	size_t					height;
	bool					grow;
	size_t					grow_val;
	std::vector<IEntity *>	entities;
	Position				head_pos;
	SnakeHead *				head;
	
};

#endif
