/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:52:10 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 13:06:01 by gsmith           ###   ########.fr       */
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
	void					print(void) const;
	bool					move_head(int x, int y);

private:
	Grid(void);
	Grid const &			operator=(Grid const & rhs) const;
	
	size_t					width;
	size_t					height;
	std::vector<IEntity *>	entities;
	std::array<int, 2>		head_pos;
	SnakeHead *				head;
};

#endif