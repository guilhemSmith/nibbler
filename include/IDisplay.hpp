/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IDisplay.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:48:20 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/21 18:04:54 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IDISPLAY_HPP
# define IDISPLAY_HPP

extern "C" {
    class IDisplay {
    public:
	virtual void	sayHello(std::string) = 0;
	virtual 	~IDisplay(void) {};
	virtual void	displayGameWindow() = 0;
    };
}

#endif
