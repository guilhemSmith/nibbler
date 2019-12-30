/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Obstacle.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:50:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 17:21:34 by gsmith           ###   ########.fr       */
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
	virtual bool		collide(void);
	virtual char		get_symbol(void) const;
	IDisplay::EMotif	get_motif(void) const;
	bool				is_mobile(void) const;

private:
	Obstacle const &	operator=(Obstacle const & rhs) const;
};

#endif
