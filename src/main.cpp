/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:49 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 18:27:46 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"
#include "Arguments.hpp"
#include "Game.hpp"
#include "IDisplay.hpp"

int		main(int argc, char * argv[]) {
	Arguments			args;
	
	try {
		args.init(argc, argv);
	} catch (Arguments::InvalidArguments inv) {
		std::cerr << inv.what() << std::endl;
		return 1;
	}

	try {
		Game	game(args.getStartingLib(), args.getWidth(), args.getHeight());

		while (game.run());
	} catch (std::exception e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}
