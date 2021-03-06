/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DisplayGLFW.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:05:38 by gsmith            #+#    #+#             */
/*   Updated: 2020/06/21 11:17:55 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include "DisplayGLFW.hpp"

float const										DisplayGLFW::vertices[216] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
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
	{GLFW_KEY_SPACE, Quit},
};

DisplayGLFW::DisplayGLFW(void): width(0), height(0), wind(NULL), eventStack(), \
	eventPolled(false), vao(0), vbo(0), shader(0), cameraView(), \
	projection(), motifMap() {
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
		y * DisplayGLFW::cell_size, "Nibbler - GLFW", NULL, NULL);
	if (this->wind == NULL) {
		throw GLFWExcept("Failed to create an GLFW window");
	}
	glfwSetWindowPos(this->wind, 0, 0);
	glfwSetWindowAspectRatio(this->wind, x * DisplayGLFW::cell_size, \
		y * DisplayGLFW::cell_size);
	glfwSetWindowSizeLimits(this->wind, x * DisplayGLFW::cell_size, x * DisplayGLFW::cell_size, \
		y * DisplayGLFW::cell_size, y * DisplayGLFW::cell_size);
	glfwMakeContextCurrent(this->wind);
	if (GLEW_OK != glewInit()) {
		throw GLFWExcept("Failed to init an Glew");
	}
	glViewport(0, 0, x * DisplayGLFW::cell_size, y * DisplayGLFW::cell_size);
	glEnable(GL_DEPTH_TEST);
	this->initCube();
	this->loadShaders();
	float dist = (float)y / 2.0f * (float)DisplayGLFW::cell_size / std::tan(glm::radians(30.0f));
	this->projection = glm::perspective(glm::radians(60.0f), \
		(float)(x * DisplayGLFW::cell_size) \
		/ (float)(y * DisplayGLFW::cell_size), 0.1f, dist + DisplayGLFW::cell_size);
	this->cameraView = glm::translate(glm::mat4(1.0f), \
		glm::vec3(-(((float)x - 1.0f) * (float)DisplayGLFW::cell_size) / 2.0f, \
		-(float)((y + 1) * DisplayGLFW::cell_size) / 2.0f, -dist));
	this->motifMap = {
		{snakeHead, {164.0f / 255.0f, 198.0f / 255.0f, 57.0f / 255.0f}},
		{snake, {135.0f / 255.0f, 169.0f / 255.0f, 107.0f / 255.0f}},
		{apple, {227.0f / 255.0f, 38.0f / 255.0f, 54.0f / 255.0f}},
		{blueberry, {33.0f / 255.0f, 171.0f / 255.0f, 205.0f / 255.0f}},
		{obstacle, {159.0f / 255.0f, 129.0f / 255.0f, 112.0f / 255.0f}},
	};
	this->keyState = {
		{GLFW_KEY_1, false},
		{GLFW_KEY_2, false},
		{GLFW_KEY_3, false},
		{GLFW_KEY_UP, false},
		{GLFW_KEY_W, false},
		{GLFW_KEY_DOWN, false},
		{GLFW_KEY_S, false},
		{GLFW_KEY_LEFT, false},
		{GLFW_KEY_A, false},
		{GLFW_KEY_RIGHT, false},
		{GLFW_KEY_D, false},
		{GLFW_KEY_ESCAPE, false},
		{GLFW_KEY_SPACE, false},
	};
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
	glUseProgram(this->shader);
	glUniform3fv(glGetUniformLocation(this->shader, "base_color"), 1, \
		&(this->motifMap[motif][0]));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, \
		GL_FALSE, glm::value_ptr(this->projection));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "view"), 1, \
		GL_FALSE, glm::value_ptr(this->cameraView));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3((float)(pos.x * DisplayGLFW::cell_size), \
		(float)((this->height - pos.y) * DisplayGLFW::cell_size), 0.0f));
	model = glm::scale(model, glm::vec3(DisplayGLFW::cell_size, \
		DisplayGLFW::cell_size, DisplayGLFW::cell_size));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "model"), 1, \
		GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void				DisplayGLFW::drawMobile(Position & pos, Direction & dest, \
							Direction & from, EMotif motif, float progression) {
	(void)from;
	(void)motif;
	glUseProgram(this->shader);
	glUniform3fv(glGetUniformLocation(this->shader, "base_color"), 1, \
		&(this->motifMap[motif][0]));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "projection"), 1, \
		GL_FALSE, glm::value_ptr(this->projection));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "view"), 1, \
		GL_FALSE, glm::value_ptr(this->cameraView));
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3((float)((pos.x + dest.x * progression) * DisplayGLFW::cell_size), \
		(float)((this->height - (pos.y + dest.y * progression)) * DisplayGLFW::cell_size), 0.0f));
	model = glm::scale(model, glm::vec3(DisplayGLFW::cell_size, \
		DisplayGLFW::cell_size, DisplayGLFW::cell_size));
	glUniformMatrix4fv(glGetUniformLocation(this->shader, "model"), 1, \
		GL_FALSE, glm::value_ptr(model));
	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void				DisplayGLFW::drawScore(int score) {
	(void)score;
}


IDisplay::EEvent	DisplayGLFW::pollEvent(void) {
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
	bool		state;
	while (!this->eventStack.empty()) {
		this->eventStack.pop();
	}
	if (glfwWindowShouldClose(this->wind)) {
		this->eventStack.push(Quit);
	}
	for (auto it = keyMap.begin(); it != keyMap.end(); it++) {
		state = glfwGetKey(this->wind, it->first);
		if (state && !this->keyState.at(it->first)) {
			this->eventStack.push(it->second);
			this->keyState.at(it->first) = true;
		} else if (!state && this->keyState.at(it->first)) {
			this->keyState[it->first] = false;
		}
	}
}

void				DisplayGLFW::initCube() {
	glGenVertexArrays(1, &(this->vao));
	glGenBuffers(1, &(this->vbo));
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, (this->vbo));
	glBufferData(GL_ARRAY_BUFFER, sizeof(DisplayGLFW::vertices), \
		DisplayGLFW::vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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