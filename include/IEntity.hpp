/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IEntity.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:00:46 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 16:42:02 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IENTITY_HPP
# define IENTITY_HPP

#include "IDisplay.hpp"

class IEntity {
public:
	virtual ~IEntity(void) {};

	virtual IEntity *			clone(void) const = 0;
	virtual bool				collide(void) = 0;
	virtual char				get_symbol(void) const = 0;
	virtual IDisplay::EMotif	get_motif(void) const = 0;

private:
};

#endif
