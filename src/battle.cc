#include <iostream>
#include <string>
#include <cctype>

#include "correct_curses.h"

#include "stats.h"

#ifndef CTRL
#define CTRL(x) ((x) & 037)
#endif

int main () {
	initscr();
	raw();
	noecho();
	scrollok(stdscr, FALSE);
	curs_set(0);

	game::Stats you(20, 5, 8), them(20, 10, 4);

	int ch = 0;
	while (ch != 'q' && ch != CTRL('c') && you.health() > 0 && them.health() > 0) {
		erase();
		printw("them:\nHealth - %d\n", them.health());
		printw("you:\nHealth - %d\nAttack - %d\nDefense - %d\n",
			you.health(), you.attack(), you.defense());
		refresh();
		ch = tolower(getch());
		switch (ch) {
			case 'a':
				you.attack(them);
				break;
			case 'h':
				you.heal(5);
				break;
		}
		them.attack(you);
	}
	if (you.health() <= 0) {
		printw("You died");
		refresh();
		getch();
	} else if (them.health() <= 0) {
		printw("You killed them");
		refresh();
		getch();
	}
	endwin();
}
