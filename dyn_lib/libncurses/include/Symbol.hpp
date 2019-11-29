/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Symbol.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 13:33:29 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/29 14:50:07 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMBOL_HPP 
# define SYMBOL_HPP 

class	Symbol {
public:
	enum color {
		COLOR_NIL,
		COLOR_PAIR_APPLE,
		COLOR_PAIR_OBSTACLE,
		COLOR_PAIR_SNAKE,
		COLOR_PAIR_HEAD
	};

	Symbol(char sym, color col);
 	~Symbol(void);

	color	get_color(void);
	char	get_sym(void);

private:
	char	_sym;
	color	_color;

	Symbol(void);
	Symbol(Symbol const &src);
	Symbol 		&operator=(Symbol const &rhs);
};

#endif
