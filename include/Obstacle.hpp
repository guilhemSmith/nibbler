/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:50:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 13:56:26 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBSTACLE_HPP
# define OBSTACLE_HPP

# include "IEntity.hpp"

class Obstacle: public IEntity {
public:
	Obstacle(void);
	Obstacle(Obstacle const & rhs);
	virtual ~Obstacle(void);

	virtual IEntity *	clone(void) const;
	virtual bool		is_collider(void) const;
	virtual char		get_symbol(void) const;

private:
	Obstacle const &	operator=(Obstacle const & rhs) const;
};

#endif