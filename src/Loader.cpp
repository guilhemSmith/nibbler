/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:32 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/28 17:45:42 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dlfcn.h>
#include <string>
#include "Loader.hpp"

Loader::Loader(int lib, size_t width, size_t height): libId(lib) {
	this->libTab = {
		{1, "libsdl2"},
		{2, "libsfml"},
	};
	this->load_lib(lib, width, height);
}

Loader::~Loader(void) {
	this->unload_lib();
}

IDisplay *				Loader::get_display(void) const {
	return this->disp;
}

void					Loader::load_lib(int lib, size_t width, size_t height) {
	std::string		libName = "";
	void *			dl_handle;
	
	try {
		libName += this->libTab.at(lib);
		libName = "./dyn_lib/" + libName + '/' + libName + ".so";
	} catch (std::out_of_range oor) {
		throw LoaderExcept("Unknown lib.");
	}
	dl_handle = dlopen(libName.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (dl_handle == NULL) {
		throw LoaderExcept("Failed to open '" + libName + '\'');
	}
	this->unload_lib();
	this->handle = dl_handle;
    this->createD = (IDisplay*(*)(void))dlsym(this->handle, "createDisplay"); 
    this->deleteD = (void(*)(IDisplay*))dlsym(this->handle, "deleteDisplay"); 
    this->disp = this->createD();
	this->disp->newWindow(width, height);
}

void					Loader::unload_lib(void) {
	if (this->handle != NULL) {
		if (this->disp != NULL) {
			this->deleteD(this->disp);
		}
		dlclose(this->handle);
	}
	this->handle = NULL;
	this->disp = NULL;
	this->createD = NULL;
	this->deleteD = NULL;
}

Loader::LoaderExcept::LoaderExcept(std::string message): message(message) {}

Loader::LoaderExcept::LoaderExcept(LoaderExcept const & rhs): \
					message(rhs.message) {}

Loader::LoaderExcept::~LoaderExcept(void) {}

char const *			Loader::LoaderExcept::what(void) const throw() {
	return this->message.c_str();
}