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
	virtual 	~IDisplay(void) {};
	virtual void	sayHello(std::string) = 0;
	virtual void	displayGameWindow() = 0;
	virtual void	eventLoop() = 0;		
	virtual void	swapDisplay(int newDisplay) = 0;
    };
}

#endif
