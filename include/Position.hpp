/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Position.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 11:39:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/05 12:54:43 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POSITION_HPP
# define POSITION_HPP
# include <cstdlib>

class Position {
public:
	Position(size_t x, size_t y);
	Position(Position const & rhs);
	~Position(void);

	Position const &	operator=(Position const & rhs);
	Position const &	clamp(size_t width, size_t height);
	size_t				to_index(size_t width) const;

	size_t	x;
	size_t	y;
};

#endif
