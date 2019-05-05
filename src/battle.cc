#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>

#include "correct_curses.h"

#include "stats.h"
#include "health_bar.h"

#ifndef CTRL
#define CTRL(x) ((x) & 037)
#endif

namespace {
	template <typename T, typename R>
	int wait_for (const std::chrono::duration<T, R> &x) {
		std::this_thread::sleep_for(x);
		return flushinp();
	}
} // namespace

int main () {
	initscr();
#ifdef HAVE_CURSES_COLOR
	if (has_colors() == TRUE) start_color();
#endif
	raw();
	noecho();
	scrollok(stdscr, FALSE);
	curs_set(0);
	timeout(50);

	game::HealthBar theirs(0, 9, 20);

	game::Stats you(20, 5, 8, 1), them(20, 10, 4, 2);

	int ch = 0;
	mvaddstr(0, 0, "them:");
	mvaddstr(1, 0, "Health");
	mvprintw(2, 0, "you:");
	mvprintw(3, 0, "Health - %d", you.health());
	mvprintw(4, 0, "Attack - %d", you.attack());
	mvprintw(5, 0, "Defense - %d", you.defense());
	refresh();
	theirs.disp();
	bool them_to_attack = false;
	while (ch != 'q' && ch != CTRL('c') && you.health() > 0 && them.health() > 0) {
		switch (ch) {
			case 'a':
				you.attack(them);
				theirs.update(them.health() * them.max_health() / 20);
				if (them.health() > 0) them_to_attack = true;
				wait_for(std::chrono::milliseconds(500));
				break;
			case 'h':
				you.heal(5);
				mvprintw(3, 9, "%d ", you.health());
				refresh();
				them_to_attack = true;
				wait_for(std::chrono::milliseconds(500));
				break;
		}
		if (them_to_attack) {
			them_to_attack = false;
			them.attack(you);
			mvprintw(3, 9, "%d ", you.health());
			refresh();
		}
		ch = tolower(getch());
	}
	timeout(-1);
	if (you.health() <= 0) {
		mvaddstr(6, 0, "You died");
		refresh();
		getch();
	} else if (them.health() <= 0) {
		mvaddstr(6, 0, "You killed them");
		refresh();
		getch();
	}
	endwin();
	return 0;
}
