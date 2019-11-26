/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:00:46 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 13:33:52 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IENTITY_HPP
# define IENTITY_HPP

class IEntity {
public:
	virtual ~IEntity(void) {};

	virtual IEntity *	clone(void) const = 0;
	virtual bool		collide(void) = 0;
	virtual char		get_symbol(void) const = 0;

private:
};

#endif