/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NcursesDisplay.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbehra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:17:41 by tbehra            #+#    #+#             */
/*   Updated: 2019/11/29 15:22:28 by tbehra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NcursesDisplay.hpp"


NcursesDisplay::NcursesDisplay(void) {
}

NcursesDisplay::~NcursesDisplay(void) {
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
	endwin();
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
	WINDOW	*stdscr = initscr();
//	SCREEN	*stdscr = newterm(termType, stdin, stdout);
	initColors();
	cbreak();
	noecho();
	timeout(0);
	keypad(stdscr, TRUE);
	curs_set(0);
//	getmaxyx(stdscr, h, w);
	(void)x;
	(void)y;
}

void	NcursesDisplay::refreshDisplay(void) {
	refresh();
}

void	NcursesDisplay::clearDisplay(void) {
	clear();
	refresh();
}

void	NcursesDisplay::drawStatic(t_position pos, EMotif motif) {
	Symbol	*sym = NULL;

	try {
		sym = &motifToSymbol.at(motif);
	}
	catch (std::out_of_range &oor) {
		return ;
	}
	move(pos.y, pos.x);
	attron(COLOR_PAIR(sym->get_color()));
	addch(sym->get_sym());
	attroff(COLOR_PAIR(sym->get_color()));
}

void	NcursesDisplay::drawMobile(t_position start, t_position stop, EMotif motif,
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

	while((ch = getch()) != ERR) {
		try {
			return this->keyboardToEvent.at(ch);
		}
		catch (std::out_of_range &oor) {
			continue ;
		}
	}
	return None;
}
