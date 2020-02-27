/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplayGLFW.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:38 by gsmith            #+#    #+#             */
/*   Updated: 2020/02/27 18:30:05 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include "DisplayGLFW.hpp"

float const										DisplayGLFW::vertices[24] = {
	-0.5, -0.5, -0.5,
	-0.5, -0.5, 0.5,
	-0.5, 0.5, 0.5,
	0.5, 0.5, 0.5,
	0.5, -0.5, 0.5,
	0.5, -0.5, -0.5,
	0.5, 0.5, -0.5,
	-0.5, 0.5, -0.5,
};

int const										DisplayGLFW::indices[36] = {
	0, 1, 2,
	0, 7, 2,

	0, 1, 4,
	0, 5, 4,

	0, 5, 6,
	0, 7, 6,

	3, 4, 5,
	3, 6, 5,

	3, 2, 7,
	3, 6, 7,

	3, 4, 1,
	3, 2, 1,
};

std::map<unsigned int, IDisplay::EEvent> const	DisplayGLFW::keyMap = {
	{GLFW_KEY_1, One},
	{GLFW_KEY_2, Two},
	{GLFW_KEY_3, Three},
	{GLFW_KEY_UP, Up},
	{GLFW_KEY_W, Up},
	{GLFW_KEY_DOWN, Down},
	{GLFW_KEY_S, Down},
	{GLFW_KEY_LEFT, Left},
	{GLFW_KEY_A, Left},
	{GLFW_KEY_RIGHT, Right},
	{GLFW_KEY_D, Right},
	{GLFW_KEY_ESCAPE, Quit},
};

DisplayGLFW::DisplayGLFW(void): width(0), height(0), wind(NULL), eventStack(), \
	eventPolled(false), vao(0), vbo(0), ebo(0), shader(0) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

DisplayGLFW::~DisplayGLFW(void) {
	if (this->shader) {
		glDeleteProgram(this->shader);
	}
	if (this->vao) {
		glDeleteVertexArrays(1, &(this->vao));
	}
	if (this->vbo) {
		glDeleteBuffers(1, &(this->vbo));
	}
	if (this->ebo) {
		glDeleteBuffers(1, &(this->ebo));
	}
	if (this->wind != NULL) {
		glfwDestroyWindow(this->wind);
		this->wind = NULL;
	}
	glfwTerminate();
}

void				DisplayGLFW::newWindow(size_t x, size_t y) {
	if (this->wind != NULL) {
		glfwDestroyWindow(this->wind);
		this->wind = NULL;
	}
	this->width = x;
	this->height = y;
	this->wind = glfwCreateWindow(x * DisplayGLFW::cell_size, \
		y * DisplayGLFW::cell_size, "nibbler", NULL, NULL);
	if (this->wind == NULL) {
		throw GLFWExcept("Failed to create an GLFW window");
	}
	glfwMakeContextCurrent(this->wind);
	if (GLEW_OK != glewInit()) {
		throw GLFWExcept("Failed to init an Glew");
	}
	glViewport(0, 0, x * DisplayGLFW::cell_size, y * DisplayGLFW::cell_size);
	glEnable(GL_DEPTH_TEST);
	this->initCube();
	this->loadShaders();
	this->clearDisplay();
	this->refreshDisplay();
}

void				DisplayGLFW::clearDisplay(void) {
	glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void				DisplayGLFW::refreshDisplay(void) {
	glfwSwapBuffers(this->wind);
    glfwPollEvents(); 
}

void				DisplayGLFW::drawStatic(Position & pos, EMotif motif) {
	(void)pos;
	(void)motif;
	// Uint32			color;
	// SDL_Rect		rect = {
	// 	static_cast<int>(pos.x * DisplayGLFW::cell_size),
	// 	static_cast<int>(pos.y * DisplayGLFW::cell_size),
	// 	DisplayGLFW::cell_size,
	// 	DisplayGLFW::cell_size,
	// };
	
	// try {
	// 	color = this->motifMap.at(motif);
	// } catch(std::out_of_range oor) {
	// 	throw GLFWExcept("Trying to render an unknown motif");
	// }
	// SDL_FillRect(this->surf, &rect, color);
}

void				DisplayGLFW::drawMobile(Position & pos, Direction & dest, \
							Direction & from, EMotif motif, float progression) {
	(void)pos;
	(void)dest;
	(void)from;
	(void)motif;
	(void)progression;
	
	// Uint32			color;
	// SDL_Rect		rect = {
	// 	static_cast<int>(pos.x * DisplayGLFW::cell_size \
	// 		+ dest.x * progression * DisplayGLFW::cell_size),
	// 	static_cast<int>(pos.y * DisplayGLFW::cell_size \
	// 		+ dest.y * progression * DisplayGLFW::cell_size),
	// 	DisplayGLFW::cell_size,
	// 	DisplayGLFW::cell_size,
	// };

	// try {
	// 	color = this->motifMap.at(motif);
	// } catch(std::out_of_range oor) {
	// 	throw GLFWExcept("Trying to render an unknown motif");
	// }
	// SDL_FillRect(this->surf, &rect, color);
	// int new_x = pos.x + dest.x;
	// if (new_x == (int)this->width) {
	// 	rect.x = 0.0;
	// 	rect.w = progression * DisplayGLFW::cell_size;
	// 	SDL_FillRect(this->surf, &rect, color);
	// } else if (new_x < 0) {
	// 	rect.x = (this->width - progression) * DisplayGLFW::cell_size;
	// 	SDL_FillRect(this->surf, &rect, color);
	// }
	// int new_y = pos.y + dest.y;
	// if (new_y == (int)this->height) {
	// 	rect.y = 0.0;
	// 	rect.h = progression * DisplayGLFW::cell_size;
	// 	SDL_FillRect(this->surf, &rect, color);
	// } else if (new_y < 0) {
	// 	rect.y = (this->height - progression) * DisplayGLFW::cell_size;
	// 	SDL_FillRect(this->surf, &rect, color);
	// }
}

void				DisplayGLFW::drawScore(int score) {
	(void)score;
	// SDL_Color White = {255, 255, 255, 255};
	// std::string value;
	
	// try {
	// 	value = std::to_string(score);
	// } catch (std::exception e) {
	// 	value = "ERR";
	// }
	// SDL_Surface* surfaceMessage = TTF_RenderText_Solid(this->font, \
	// 	value.c_str(), White);
	// SDL_BlitSurface(surfaceMessage, NULL, this->surf, &this->score_pos);
	// SDL_FreeSurface(surfaceMessage);
}


IDisplay::EEvent	DisplayGLFW::pollEvent(void) {
	if (glfwWindowShouldClose(this->wind)) {
		return Quit;
	}
	if (!this->eventPolled) {
		this->eventPolled = true;
		this->pollAllEvent();
	}
	if (!this->eventStack.empty()) {
		EEvent event = this->eventStack.top();
		this->eventStack.pop();
		return (event);
	} else {
		this->eventPolled = false;
		return None;
	}
}

void				DisplayGLFW::pollAllEvent()  {
	while (!this->eventStack.empty()) {
		this->eventStack.pop();
	}
	for (auto it = keyMap.begin(); it != keyMap.end(); it++) {
		if (glfwGetKey(this->wind, it->first)) {
			this->eventStack.push(it->second);
		}
	}
}

void				DisplayGLFW::initCube() {
	glGenVertexArrays(1, &(this->vao));
	glGenBuffers(1, &(this->vbo));
	glGenBuffers(1, &(this->ebo));
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, (this->vbo));
	glBufferData(GL_ARRAY_BUFFER, sizeof(DisplayGLFW::vertices), \
		DisplayGLFW::vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, (this->ebo));
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(DisplayGLFW::indices), \
		DisplayGLFW::indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void				DisplayGLFW::loadShaders() {
	unsigned int		shaders[2];
	int					success;
	char				err_log[512];
	
	shaders[0] = compileShader("dyn_lib/libglfw/shaders/vertex.glsl", \
		GL_VERTEX_SHADER);
	shaders[1] = compileShader("dyn_lib/libglfw/shaders/fragment.glsl", \
		GL_FRAGMENT_SHADER);
	this->shader = glCreateProgram();
	glAttachShader(this->shader, shaders[0]);
	glAttachShader(this->shader, shaders[1]);
	glLinkProgram(this->shader);
	glGetProgramiv(this->shader, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->shader, 512, NULL, err_log);
		throw GLFWExcept(err_log);
	}
	glDeleteShader(shaders[0]);
	glDeleteShader(shaders[1]);
}

unsigned int		DisplayGLFW::compileShader(const char *filename, \
	unsigned int kind) {
	std::ifstream		ifstr;
	std::string			fileContent;
	const char			*filechars;
	unsigned int		shader;
	int					success;
	char				err_log[512];


	ifstr = std::ifstream(filename);
	fileContent = std::string((std::istreambuf_iterator<char>(ifstr)),
		std::istreambuf_iterator<char>());
	filechars = fileContent.c_str();
	shader = glCreateShader(kind);
	glShaderSource(shader, 1, &filechars, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, err_log);
		throw GLFWExcept(err_log);
	}
	return shader;
}

DisplayGLFW::GLFWExcept::GLFWExcept(std::string message): message(message) {}

DisplayGLFW::GLFWExcept::~GLFWExcept(void) {}

DisplayGLFW::GLFWExcept::GLFWExcept(GLFWExcept const & rhs): \
						message(rhs.message) {}

char const *		DisplayGLFW::GLFWExcept::what(void) const throw() {
	return this->message.c_str();
}