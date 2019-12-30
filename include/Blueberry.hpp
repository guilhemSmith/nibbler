/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Blueberry.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 14:15:47 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 18:05:39 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BLUEBERRY_HPP
# define BLUEBERRY_HPP

# include "Apple.hpp"

class Blueberry: public Apple {
public:
	Blueberry(Score & score);
	Blueberry(Blueberry const & rhs);
	virtual ~Blueberry(void);

	virtual bool				collide(void);
	virtual char				get_symbol(void) const;
	virtual IDisplay::EMotif	get_motif(void) const;
	virtual size_t				grow_value(void) const;
	bool						rot(void);

private:
	Blueberry(void);
	Blueberry const &	operator=(Blueberry const & rhs) const;

	int					value;
	static int const	new_val = 200;
};

#endif