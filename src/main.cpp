/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:49 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/27 18:14:16 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"
#include "Arguments.hpp"
#include "Game.hpp"
#include "IDisplay.hpp"

#include <unistd.h>

int		main(int argc, char * argv[]) {
	Arguments		args;
	
	try {
		args.init(argc, argv);
	} catch (Arguments::InvalidArguments inv) {
		std::cerr << inv.what() << std::endl;
		return 1;
	}
	std::cout << "lib: " << args.getStartingLib() \
		<< "\nwidth: " << args.getWidth() \
		<< "\nheight: " << args.getHeight() << std::endl;
	Game			game(args.getWidth(), args.getHeight());
	for (int i = 0; i < args.getWidth(); i++){
		game.spawn_obstacle(i, 0);
		game.spawn_obstacle(i, args.getHeight() - 1);
	}
	for (int i = 1; i < args.getHeight() - 1; i++) {
		game.spawn_obstacle(0, i);
		game.spawn_obstacle(args.getWidth() - 1, i);
	}
	game.spawn_obstacle(args.getWidth() / 3, args.getHeight() / 2);
	game.spawn_apple(args.getWidth() / 2 + 5, args.getHeight() / 2);
	game.spawn_apple(args.getWidth() / 2 + 6, args.getHeight() / 2);
	game.spawn_apple(args.getWidth() / 2 + 7, args.getHeight() / 2);
	game.print_grid();
	std::cout << "score: " << game.get_score() << std::endl;
	while (game.move(1, 0));
	game.print_grid();
	std::cout << "score: " << game.get_score() << std::endl;
	void *		handle = dlopen("./dyn_lib/libsdl2/libsdl2.so", RTLD_LAZY | RTLD_LOCAL);
	IDisplay		*(*createDisplay)(void) = (IDisplay*(*)(void))dlsym(handle, "createDisplaySDL2");
    IDisplay		*disp = createDisplay();
	disp->newWindow(args.getWidth(), args.getHeight());
	// usleep(5000000);
	dlclose(handle);
	return 0;
}