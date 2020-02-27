/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplayGLFW.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:25:22 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/27 14:58:34 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAYGLFW_HPP
# define DISPLAYGLFW_HPP

# include <exception>
# include <string>
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <map>
# include <stack>
# include "IDisplay.hpp"

class DisplayGLFW: public IDisplay {
public:
	class GLFWExcept: public std::exception {
	public:
		GLFWExcept(std::string message);
		GLFWExcept(GLFWExcept const & rhs);
		~GLFWExcept(void);

		virtual char const *	what(void) const throw();

	private:
		GLFWExcept(void);
		GLFWExcept const &		operator=(GLFWExcept const & rhs);

		std::string				message;
	};
	DisplayGLFW(void);
	~DisplayGLFW(void);


	void						newWindow(size_t x, size_t y);
	void						clearDisplay(void);
	void						refreshDisplay(void);
	void						drawStatic(Position & pos, EMotif motif);
	void						drawMobile(Position & pos, Direction & dest, \
									Direction & from, \
									EMotif motif, float progression);
	void						drawScore(int score);
	EEvent 						pollEvent(void);
private:
	DisplayGLFW(DisplayGLFW const & rhs);
	DisplayGLFW const &			operator=(DisplayGLFW const & rhs);
	void						pollAllEvent();
	
	size_t							width;
	size_t							height;
	GLFWwindow *					wind;
	std::stack<EEvent>				eventStack;
	bool							eventPolled;

	static size_t const							cell_size = 16;
	static size_t const							keyMapSize = 12;
	static std::map<unsigned int, EEvent> const	keyMap;

};

#endif