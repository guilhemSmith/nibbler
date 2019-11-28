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


#define LIBSDL 1
#define LIBSFML 2
#define LIB_X 3

IDisplay	*init_display(int starting_lib, void **dl_handle) {
    IDisplay		*(*createDisplay)(void);
    IDisplay		*disp;

    if (starting_lib == LIBSFML) {
		*dl_handle = dlopen("./dyn_lib/libsfml/libsfml.so",
			RTLD_LAZY | RTLD_LOCAL);
		if (!*dl_handle) {
			std::cerr << "error occured while loading libsfml.so" << std::endl;
			return NULL;
		}
    }
    else {
		return NULL;
    }
    createDisplay = (IDisplay*(*)(void))dlsym(*dl_handle, "createDisplay"); 
    disp = createDisplay();
    return (disp);
}

//TODO: get rid of C style casts (createDisplay, deleteDisplay)
//TODO: remplacer !disp et !deleteDisplay par try catch ?
//TODO: passer initialize en methode
void	initialize(Game &game, int width, int height) {
	for (int i = 0; i < width; i++){
		game.spawn_obstacle(i, 0);
		game.spawn_obstacle(i, height - 1);
	}

	for (int i = 1; i < height - 1; i++) {
		game.spawn_obstacle(0, i);
		game.spawn_obstacle(width - 1, i);
	}

	game.spawn_obstacle(width / 3, height / 2);
	game.spawn_apple(width / 2 + 5, height / 2);
	game.spawn_apple(width / 2 + 6, height / 2);
	game.spawn_apple(width / 2 + 7, height / 2);
}

int		main(int argc, char * argv[]) {
	Arguments			args;
	IDisplay			*disp;	
	void				(*deleteDisplay)(IDisplay *disp);
	void				*dl_handle = nullptr;
	IDisplay::EEvent	event;
	int					mov_x;
	int					mov_y;
	
	try {
		args.init(argc, argv);
	} catch (Arguments::InvalidArguments inv) {
		std::cerr << inv.what() << std::endl;
		return 1;
	}

	Game game(args.getWidth(), args.getHeight());
	initialize(game, args.getWidth(), args.getHeight());

	disp = init_display(args.getStartingLib(), &dl_handle);
	if (!disp) {
	    std::cerr << "Couldn't open the library" << std::endl;
	    return 1;
	}
	deleteDisplay = (void(*)(IDisplay *))dlsym(dl_handle, "deleteDisplay"); 
	if (!deleteDisplay) {
	    std::cerr << "Couldn't load deleteDisplay" << std::endl;
	    return 1;
	}
	disp->newWindow(args.getWidth(), args.getHeight());
	disp->refreshDisplay();
	game.set_display(disp);

	mov_x = 1;
	mov_y = 0;
	while (game.run()) {
		while ((event = disp->pollEvent()) != IDisplay::None) {
			std::cout << "Event : " << event << std::endl;
			if (event == IDisplay::Quit) {
				game.quit_game();
				break;
			}
			if (event == IDisplay::Up && mov_x != 0) {
				mov_x = 0;
				mov_y = -1;
			}
			if (event == IDisplay::Down && mov_x != 0) {
				mov_x = 0;
				mov_y = 1;
			}
			if (event == IDisplay::Left && mov_y != 0) {
				mov_x = -1;
				mov_y = 0;
			}
			if (event == IDisplay::Right && mov_y != 0) {
				mov_x = 1;
				mov_y = 0;
			}
		}
		usleep(300000);
		game.move(mov_x, mov_y);	
	}
	deleteDisplay(disp);
	dlclose(dl_handle);
	return 0;
}
