/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeHead.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:54:55 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 11:30:57 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKEHEAD_HPP
# define SNAKEHEAD_HPP

# include "Snake.hpp"

class SnakeHead: public Snake {
public:
	SnakeHead(int x, int y, int tail_x, int tail_y);
	SnakeHead(SnakeHead const & rhs);
	virtual ~SnakeHead(void);

	virtual IEntity *			clone(void) const;
	virtual char				get_symbol(void) const;
	std::array<int, 2>			get_tail(void) const;
	void						forward_tail(int x, int y);

private:
	SnakeHead(void);
	SnakeHead const &			operator=(SnakeHead const & rhs) const;

	std::array<int, 2>			tail;	
};

#endif