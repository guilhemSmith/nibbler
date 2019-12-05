/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesDisplay.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmith <gsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:17:41 by tbehra            #+#    #+#             */
/*   Updated: 2019/12/05 12:03:29 by gsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcursesDisplay.hpp"


NcursesDisplay::NcursesDisplay(void): _window(NULL) {
}

NcursesDisplay::~NcursesDisplay(void) {
	if (_window != NULL)
		delwin(_window);
	endwin();
}

static Symbol symSnake('o', Symbol::COLOR_PAIR_SNAKE);
static Symbol symSnakeHead('X', Symbol::COLOR_PAIR_HEAD);
static Symbol symApple('@', Symbol::COLOR_PAIR_APPLE);
static Symbol symObstacle('*', Symbol::COLOR_PAIR_OBSTACLE);

const std::map<IDisplay::EMotif, Symbol &> NcursesDisplay::motifToSymbol = {
	{snake, symSnake},
	{apple, symApple},
	{snakeHead, symSnakeHead},
	{obstacle, symObstacle},
};

const std::map<int, IDisplay::EEvent> NcursesDisplay::keyboardToEvent = {
	{'q', IDisplay::Quit},
	{KEY_UP, IDisplay::Up},
	{KEY_DOWN, IDisplay::Down},
	{KEY_LEFT, IDisplay::Left},
	{KEY_RIGHT, IDisplay::Right},
	{'1', IDisplay::One},
	{'2', IDisplay::Two},
	{'3', IDisplay::Three},
};

IDisplay *createDisplay(void) {
	return new NcursesDisplay();
}

void	deleteDisplay(IDisplay *disp) {
	delete disp;
}

void	NcursesDisplay::initColors(void) {
	start_color();
	init_pair(Symbol::COLOR_PAIR_SNAKE, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Symbol::COLOR_PAIR_HEAD, COLOR_YELLOW, COLOR_BLACK);
	init_pair(Symbol::COLOR_PAIR_APPLE, COLOR_RED, COLOR_BLACK);
	init_pair(Symbol::COLOR_PAIR_OBSTACLE, COLOR_BLUE, COLOR_RED);
}

void	NcursesDisplay::newWindow(size_t x, size_t y) {
	initscr();
	if (_window)
		delwin(_window);
	_window = newwin(y, x, 0, 0);
//	SCREEN	*secscr = newterm(NULL, stdin, stdout);

	initColors();
	cbreak();
	noecho();
	wtimeout(_window, 0);
	keypad(_window, TRUE);
	curs_set(0);
//	getmaxyx(stdscr, h, w);
}

void	NcursesDisplay::refreshDisplay(void) {
	wrefresh(_window);
}

void	NcursesDisplay::clearDisplay(void) {
	wclear(_window);
	wrefresh(_window);
}

void	NcursesDisplay::drawStatic(Position pos, EMotif motif) {
	Symbol	*sym = NULL;

	try {
		sym = &motifToSymbol.at(motif);
	}
	catch (std::out_of_range &oor) {
		return ;
	}
	wmove(_window, pos.y, pos.x);
	wattron(_window, COLOR_PAIR(sym->get_color()));
	waddch(_window, sym->get_sym());
	wattroff(_window, COLOR_PAIR(sym->get_color()));
}

void	NcursesDisplay::drawMobile(Position start, Position stop, EMotif motif,
		int progression)
{
	(void)start;
	(void)stop;
	(void)motif;
	(void)progression;
}	

void	NcursesDisplay::drawScore(int score) {
	(void)score;
}

IDisplay::EEvent NcursesDisplay::pollEvent(void) {
	int ch;

	while((ch = wgetch(_window)) != ERR) {
		try {
			return this->keyboardToEvent.at(ch);
		}
		catch (std::out_of_range &oor) {
			continue ;
		}
	}
	return None;
}
