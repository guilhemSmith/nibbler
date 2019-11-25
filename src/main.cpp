/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:49 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/20 14:23:08 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"
#include "Print.hpp"
#include "Arguments.hpp"
#include "Game.hpp"
#include "IDisplay.hpp"

#include "../dyn_lib/libsfml/include/FSMLDisplay.hpp"

#define LIBSDL 0
#define LIBSFML 1
#define LIBPRINT 2

IDisplay	*init_display(int starting_lib, void *dl_handle) {
    IDisplay		*(*createDisplay)(void);
    IDisplay		*disp;

    if (starting_lib == LIBSFML) {
	dl_handle = dlopen("./dyn_lib/libsfml/libsfml.so",
		RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle) {
	    std::cerr << "error occured while loading libsfml.so" << std::endl;
	    return NULL;
	}
	//TODO:  get rid of C style casts
    }
    else if (starting_lib == LIBPRINT) {
	dl_handle = dlopen("./dyn_lib/libprint/libprint.so",
		RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle) {
	    std::cerr << "error occured while loading libprint.so" << std::endl;
	    return NULL;
	}
    }
    else {
	return NULL;
    }
    createDisplay = (IDisplay*(*)(void))dlsym(dl_handle, "createDisplay"); 
    disp = createDisplay();
    return (disp);
}

int		main(int argc, char * argv[]) {
	Arguments	args;
	IDisplay	*disp;	
	void		*dl_handle = nullptr;
	
	try {
		args.init(argc, argv);
	} catch (Arguments::InvalidArguments inv) {
		std::cerr << inv.what() << std::endl;
		return 1;
	}
	std::cout << "lib: " << args.getStartingLib() \
		<< "\nwidth: " << args.getWidth() \
		<< "\nheight: " << args.getHeight() << std::endl;
	Game	game(args.getWidth(), args.getHeight());
	for (int i = 0; i < args.getWidth(); i++){
		game.spawn_obstacle(i, 0);
		game.spawn_obstacle(i, args.getHeight() - 1);
	}
	for (int i = 1; i < args.getHeight() - 1; i++) {
		game.spawn_obstacle(0, i);
		game.spawn_obstacle(args.getWidth() - 1, i);
	}
	game.spawn_apple(args.getWidth() / 2, args.getHeight() / 2);
	game.print_grid();

	disp = init_display(args.getStartingLib(), dl_handle);
	if (disp == NULL) {
	    std::cerr << "Couldn't open the library" << std::endl;
	    return 1;
	}
	disp->sayHello("world");
	disp->displayGameWindow();
	disp->eventLoop();

	dlclose(dl_handle);
	return 0;
}
