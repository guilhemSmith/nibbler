/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Snake.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:54:55 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/22 13:34:28 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SNAKE_HPP
# define SNAKE_HPP

# include <array>
# include "IEntity.hpp"

class Snake: public IEntity {
public:
	Snake(int x, int y);
	Snake(Snake const & rhs);
	virtual ~Snake(void);

	virtual IEntity *			clone(void) const;
	virtual bool				collide(void);
	virtual char				get_symbol(void) const;
	std::array<int, 2>			get_dir() const;
	void						set_dir(int x, int y);

private:
	Snake(void);
	Snake const &				operator=(Snake const & rhs) const;

	std::array<int, 2>			dir;
};

#endif