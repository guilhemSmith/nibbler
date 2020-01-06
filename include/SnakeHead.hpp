/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeHead.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:54:55 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 13:12:17 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKEHEAD_HPP
# define SNAKEHEAD_HPP

# include "SnakeBody.hpp"

class SnakeHead: public SnakeBody {
public:
	SnakeHead(Direction dir, Position tail_pos);
	SnakeHead(SnakeHead const & rhs);
	virtual ~SnakeHead(void);

	virtual IEntity *			clone(void) const;
	virtual char				get_symbol(void) const;
	IDisplay::EMotif			get_motif(void) const;

	Position		get_tail(void) const;
	void						set_tail(Position pos);

private:
	SnakeHead(void);
	SnakeHead const &			operator=(SnakeHead const & rhs) const;

	Position		tail;	
};

#endif
