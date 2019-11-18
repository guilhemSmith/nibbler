/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:39:49 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/18 17:02:41 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "system.hpp"
#include "Print.hpp"

int		main(void) {
	void *		dl_handle = dlopen("libPrint.so", RTLD_LAZY | RTLD_LOCAL);
	if (!dl_handle) {
		std::cerr << "error occured while loading libprint.so" << std::endl;
		return 1;
	}
	void		(*sayHello)(std::string);
	sayHello = (void(*)(std::string))dlsym(dl_handle, "sayHello");
	if (!sayHello) {
		std::cerr << "error occured while loading sayHello" << std::endl;
		dlclose(dl_handle);
		return 1;
	}
	sayHello("World");
	dlclose(dl_handle);
	return 0;
}