/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:50:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 16:49:32 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLE_HPP
# define APPLE_HPP

# include "IEntity.hpp"

class Apple: public IEntity {
public:
	Apple(int & score);
	Apple(Apple const & rhs);
	virtual ~Apple(void);

	virtual IEntity *	clone(void) const;
	virtual bool		collide(void);
	virtual char		get_symbol(void) const;
	IDisplay::EMotif	get_motif(void) const;

private:
	Apple(void);
	Apple const &	operator=(Apple const & rhs) const;

	int &				score;

	void				increment_score(void);

	static int const	value;
};

#endif
