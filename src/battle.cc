#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>

#include "correct_curses.h"

#include "stats.h"

#ifndef CTRL
#define CTRL(x) ((x) & 037)
#endif

class HealthBar {
	WINDOW *win;
	int max_health;
	int cur_health;
	int border_ch[8];
	bool has_color;
	short pairs[3];

public:
	HealthBar (int ul_y, int ul_x, int max,
	int b0 = 0, int b1 = 0, int b2 = 0, int b3 = 0, int b4 = 0, int b5 = 0, int b6 = 0, int b7 = 0):
	max_health(max), cur_health(max), border_ch{b0, b1, b2, b3, b4, b5, b6, b7} {
		win = newwin(3, max + 2, ul_y, ul_x);
		has_color = false;
#ifdef HAVE_CURSES_COLOR
		// We assume color is started
		if (has_colors() == TRUE) {
			has_color = true;
			init_pair(40, COLOR_GREEN, COLOR_BLACK); pairs[0] = 40;
			init_pair(41, COLOR_YELLOW, COLOR_BLACK); pairs[1] = 41;
			init_pair(42, COLOR_RED, COLOR_BLACK); pairs[2] = 42;
		}
#endif
	}

	// Update new health and display (assuming no changes)
	void update (int h) {
		if (h < 0 || h > max_health) return;
#ifdef HAVE_CURSES_COLOR
		if (has_color) {
			if (h <= max_health / 10)
				wattron(win, COLOR_PAIR(pairs[2]));
			else if (h <= max_health / 2)
				wattron(win, COLOR_PAIR(pairs[1]));
			else
				wattron(win, COLOR_PAIR(pairs[0]));
			mvwhline(win, 1, 1, '#', h);
			wattron(win, COLOR_PAIR(0));
		} else {
			mvwhline(win, 1, 1, '#', h);
		}
#else
			mvwhline(win, 1, 1, '#', h);
#endif
		mvwhline(win, 1, h + 1, ' ', max_health - h);
		cur_health = h;
		wrefresh(win);
	}

	// Assume changes and display
	void disp () {
		wborder(win, border_ch[0], border_ch[1], border_ch[2], border_ch[3], border_ch[4], border_ch[5], border_ch[6], border_ch[7]);
#ifdef HAVE_CURSES_COLOR
		if (has_color) {
			if (cur_health <= max_health / 10)
				wattron(win, COLOR_PAIR(pairs[2]));
			else if (cur_health <= max_health / 2)
				wattron(win, COLOR_PAIR(pairs[1]));
			else
				wattron(win, COLOR_PAIR(pairs[0]));
			mvwhline(win, 1, 1, '#', cur_health);
			wattron(win, COLOR_PAIR(0));
		} else {
			mvwhline(win, 1, 1, '#', cur_health);
		}
#else
		mvwhline(win, 1, 1, '#', cur_health);
#endif
		mvwhline(win, 1, cur_health + 1, ' ', max_health - cur_health);
		wrefresh(win);
	}

	~HealthBar () {
		delwin(win);
	}
};

template <typename T, typename R>
int wait_for (const std::chrono::duration<T, R> &x) {
	std::this_thread::sleep_for(x);
	return flushinp();
}

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

	HealthBar theirs(0, 9, 20);

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
