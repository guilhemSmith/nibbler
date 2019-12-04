/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Direction.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:22:37 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/04 17:52:31 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTION_HPP
# define DIRECTION_HPP
# include <cstdlib>

class Direction {
public:
	Direction(int x, int y);
	Direction(Direction const & rhs);
	~Direction(void);

	Direction const &	operator=(Direction const & rhs);
	Direction const &	clamp(void);
	size_t				length(void) const;
	bool				is_opposed_to(Direction const & rhs) const;

	int	x;
	int	y;
};

#endif