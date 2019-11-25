/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:49 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/25 17:03:23 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"
#include "Print.hpp"
#include "Arguments.hpp"
#include "Game.hpp"

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
	// for (int i = 1; i < args.getHeight() - 1; i++) {
	// 	game.spawn_obstacle(0, i);
	// 	game.spawn_obstacle(args.getWidth() - 1, i);
	// }
	game.spawn_obstacle(args.getWidth() / 3, args.getHeight() / 2);
	game.spawn_apple(args.getWidth() / 2 + 5, args.getHeight() / 2);
	game.spawn_apple(args.getWidth() / 2 + 6, args.getHeight() / 2);
	game.spawn_apple(args.getWidth() / 2 + 7, args.getHeight() / 2);
	game.print_grid();
	std::cout << "score: " << game.get_score() << std::endl;
	while (game.move(1, 0));
	game.print_grid();
	std::cout << "score: " << game.get_score() << std::endl;
	// void *		dl_handle = dlopen("dyn_lib/libprint/libPrint.so", RTLD_LAZY | RTLD_LOCAL);
	// if (!dl_handle) {
	// 	std::cerr << "error occured while loading libprint.so" << std::endl;
	// 	return 1;
	// }
	// void		(*sayHello)(std::string);
	// sayHello = (void(*)(std::string))dlsym(dl_handle, "sayHello");
	// if (!sayHello) {
	// 	std::cerr << "error occured while loading sayHello" << std::endl;
	// 	dlclose(dl_handle);
	// 	return 1;
	// }
	// sayHello("World");
	// dlclose(dl_handle);
	return 0;
}