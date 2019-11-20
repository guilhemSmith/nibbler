/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:50:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 13:58:18 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLE_HPP
# define APPLE_HPP

# include "IEntity.hpp"

class Apple: public IEntity {
public:
	Apple(void);
	Apple(Apple const & rhs);
	virtual ~Apple(void);

	virtual IEntity *	clone(void) const;
	virtual bool		is_collider(void) const;
	virtual char		get_symbol(void) const;

private:
	Apple const &	operator=(Apple const & rhs) const;
};

#endif