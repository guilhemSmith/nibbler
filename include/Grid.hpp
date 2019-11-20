/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Grid.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:52:10 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:01:44 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_HPP
# define GRID_HPP

# include <vector>
# include "IEntity.hpp"

class Grid {
public:
	Grid(size_t width, size_t height);
	Grid(Grid const & rhs);
	~Grid(void);

	bool					spawn(IEntity *entity, size_t x, size_t y);
	void					print(void) const;

private:
	Grid(void);
	Grid const &			operator=(Grid const & rhs) const;
	
	size_t					width;
	size_t					height;
	std::vector<IEntity *>	entities;
};

#endif