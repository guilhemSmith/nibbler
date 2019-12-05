/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeTail.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 11:28:24 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 13:19:26 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKETAIL_HPP
# define SNAKETAIL_HPP

# include "SnakeBody.hpp"

class SnakeTail: public SnakeBody {
public:
	SnakeTail(Direction dir);
	SnakeTail(SnakeTail const & rhs);
	virtual ~SnakeTail(void);
	
	virtual bool				collide(void);
	
private:
	SnakeTail(void);
	SnakeTail const &			operator=(SnakeTail const & rhs) const;
};

#endif