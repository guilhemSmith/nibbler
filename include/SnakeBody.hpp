/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeBody.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:54:55 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 13:06:52 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKEBODY_HPP
# define SNAKEBODY_HPP

# include "Direction.hpp"
# include "Position.hpp"
# include "IEntity.hpp"

class SnakeBody: public IEntity {
public:
	SnakeBody(Direction dir);
	SnakeBody(SnakeBody const & rhs);
	virtual ~SnakeBody(void);

	virtual IEntity *			clone(void) const;
	virtual bool				collide(void);
	virtual char				get_symbol(void) const;
	IDisplay::EMotif			get_motif(void) const;
	Direction					get_dir() const;
	void						set_dir(Direction dir);
	Position					get_dest(Position pos) const;

private:
	SnakeBody(void);
	SnakeBody const &			operator=(SnakeBody const & rhs) const;

	Direction					dir;
};

#endif
