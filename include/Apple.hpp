/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Apple.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:50:21 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 14:26:02 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef APPLE_HPP
# define APPLE_HPP

# include "IEntity.hpp"
# include "Score.hpp"

class Apple: public IEntity {
public:
	Apple(Score & score);
	Apple(Apple const & rhs);
	virtual ~Apple(void);

	virtual IEntity *			clone(void) const;
	virtual bool				collide(void);
	virtual char				get_symbol(void) const;
	virtual IDisplay::EMotif	get_motif(void) const;
	virtual size_t				grow_value(void) const;
	bool						is_mobile(void) const;

protected:
	Score &						score;

private:
	Apple(void);
	Apple const &				operator=(Apple const & rhs) const;


	static int const			value;
};

#endif
