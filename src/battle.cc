#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>
#include <cmath>

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

	int expLevel (int level) {
		if (level == 1) return 0;
		double result = 20 * std::pow(level, 1.7);
		double tens = std::pow(10, std::ceil(std::log10(result) - 3));
		return std::floor(20 * std::pow(level, 1.7) / tens) * tens;
	}

	int cumLevel (int level) {
		int sum = 0;
		for (int i = 1; i <= level; ++i) sum += expLevel(i);
		return sum;
	}

	class Player : public game::Stats {
	public:
		game::HealthBar healthbar;

		Player (int h, int a, int d, int s, int b_h, int y, int x):
		Stats(h, a, d, s),
		healthbar(y, x, b_h) {};

		// Update health bar based off health stat
		void updateBar () noexcept {
			healthbar.update(health_ * healthbar.max_health() / max_health_);
		}

		int hit (Player &other) const noexcept {
			other.health_ -= attack_ - other.defense_ + 1;
			other.updateBar();
			return attack_ - other.defense_ + 1;
		}

		int heal (int amt) noexcept {
			if (amt < 0) return 0;
			int oh = health_;
			health_ = health_ + amt < max_health_ ? health_ + amt : max_health_;
			updateBar();
			return health_ - oh;
		}
	}; // class Player
} // namespace

int main (int argc, char *argv[]) {
	initscr();
#ifdef HAVE_CURSES_COLOR
	if (has_colors() == TRUE) start_color();
#endif
	raw();
	noecho();
	scrollok(stdscr, FALSE);
	curs_set(0);
	// timeout(50);

	Player you(20, 5, 8, 1, 20, 3, 9), them(20, 10, 4, 2, 20, 0, 9);

	int ch = 0;
	mvaddstr(0, 0, "them:");
	mvaddstr(1, 0, "Health");
	mvprintw(3, 0, "you:");
	mvprintw(4, 0, "Health", you.health());
	mvprintw(6, 0, "Attack - %d", you.attack());
	mvprintw(7, 0, "Defense - %d", you.defense());
	refresh();
	them.healthbar.disp();
	you.healthbar.disp();
	auto your_action = [&] {
		switch (ch) {
			case 'a':
				you.hit(them);
				break;
			case 'h':
				you.heal(5);
				break;
		}
	};
	while (ch != 'q' && ch != CTRL('c') && you.health() > 0 && them.health() > 0) {
		ch = tolower(getch()); if (ch == 'q' || ch == CTRL('c')) break;
		if (you.speed() > them.speed()) {
			your_action();
			wait_for(std::chrono::milliseconds(500));
			if (them.health() > 0) them.hit(you);
		} else {
			them.hit(you);
			wait_for(std::chrono::milliseconds(500));
			if (you.health() > 0) your_action();
		}
		wait_for(std::chrono::milliseconds(350));
	}
	timeout(-1);
	if (you.health() <= 0) {
		mvaddstr(8, 0, "You died");
		refresh();
		getch();
	} else if (them.health() <= 0) {
		mvaddstr(8, 0, "You killed them");
		refresh();
		getch();
	}
	endwin();
	return 0;
}
