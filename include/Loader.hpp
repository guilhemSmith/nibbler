/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Loader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:07:40 by gsmith            #+#    #+#             */
/*   Updated: 2019/11/28 17:42:10 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_HPP
# define LOADER_HPP

#include <map>
#include <exception>
#include <string>
#include "IDisplay.hpp"

class Loader {
public:
	class LoaderExcept: std::exception {
	public:
		LoaderExcept(std::string message);
		LoaderExcept(LoaderExcept const & rhs);
		~LoaderExcept(void);

		char const *			what(void) const throw();

	private:
		LoaderExcept(void);
		LoaderExcept const &	operator=(LoaderExcept const & rhs);
		
		std::string				message;
	};
	Loader(int lib, size_t width, size_t height);
	~Loader(void);

	IDisplay *					get_display(void) const;
	void						load_lib(int lib, size_t width, size_t height);

private:
	Loader(void);
	Loader(Loader const & rhs);
	Loader const &				operator=(Loader const & rhs);

	int							libId;
	std::map<int, std::string>	libTab;
	void *						handle;
    IDisplay *					disp;
    IDisplay *					(*createD)(void);
    void						(*deleteD)(IDisplay *disp);

	void						unload_lib(void);
};

#endif