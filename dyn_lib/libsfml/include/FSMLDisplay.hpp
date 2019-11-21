/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FSMLDisplay.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:20:13 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/21 18:03:17 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FSML_DISPLAY_HPP
# define FSML_DISPLAY_HPP

# include "IDisplay.hpp"
# include <SFML/Graphics.hpp>

class	FSMLDisplay: public IDisplay {
	public:
		FSMLDisplay(void);
		virtual ~FSMLDisplay(void);
		sf::RenderWindow	*getWindow(void) const;

	private:
		FSMLDisplay(FSMLDisplay const &src);
		FSMLDisplay &operator=(FSMLDisplay const &rhs);
		sf::RenderWindow	*_window;
};

#endif
