/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Score.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 12:12:40 by gsmith            #+#    #+#             */
/*   Updated: 2019/12/10 13:12:45 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCORE_HPP
# define SCORE_HPP

class Score {
public:
	Score(void);
	~Score(void);

	int					increase_speed(void);
	int					get_score(void) const;
	void				increment_score(int amount);

private:
	Score(Score const & rhs);
	Score const &		operator=(Score const & rhs);

	int					value;
	int					speedup;

	static int const	palier = 300;
};

#endif