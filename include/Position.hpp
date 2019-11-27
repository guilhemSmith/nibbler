/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Position.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:39:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 13:07:07 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITION_HPP
# define POSITION_HPP

class Position {
public:
	Position(size_t x, size_t y);
	Position(Position const & rhs);
	~Position(void);
	Position const &	operator=(Position const & rhs);

	size_t				get_x(void) const;
	size_t				get_y(void) const;
	void				set_x(size_t x);
	void				set_y(size_t y);

private:
	Position(void);

	size_t				x;
	size_t				y;
};

#endif
