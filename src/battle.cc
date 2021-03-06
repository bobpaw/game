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
	int wait_for (const std::chrono::duration<T, R>& x) {
		std::this_thread::sleep_for(x);
		return flushinp();
	}

	int expLevel (int level) {
		if (level == 1) return 0;
		double result = 20 * std::pow(level, 1.7);
		double tens = std::pow(10, std::ceil(std::log10(result) - 3));
		return static_cast<int>(std::floor(result / tens) * tens);
	}

	int cumLevel (int level) {
		int sum = 0;
		for (int i = 1; i <= level; ++i) sum += expLevel(i);
		return sum;
	}

	class Player: public game::Stats {
	private:
		std::string name_;
	public:
		game::HealthBar healthbar;
		int level, xp;

		Player (std::string nam, int h, int a, int d, int s, int b_h, int y, int x):
			Stats(h, a, d, s),
			healthbar(y, x, b_h), level(1), xp(0), name_(nam) {};

		const char* name () const noexcept {
			return name_.c_str();
		}

		// Update health bar based off health stat
		void updateBar () noexcept {
			healthbar.update(health_ * healthbar.max_health() / max_health_);
		}

		int hit (Player& other) const noexcept {
			int ret = Stats::hit(other);
			other.updateBar();
			return ret;
		}

		int heal (int amt) noexcept {
			int ret = Stats::heal(amt);
			updateBar();
			return ret;
		}
	}; // class Player
} // namespace

#if defined(VA_ARGS_NONE)
#define b_log(str, ...) do { \
scroll(log); \
mvwprintw(log, 11, 0, str, __VA_ARGS__); \
box(log_box, 0, 0); \
wrefresh(log_box); \
wrefresh(log); } while (0)
#elif defined(VA_ARGS_OPT)
#define b_log(str, ...) do { \
scroll(log); \
mvwprintw(log, 11, 0, str __VA_OPT__(,) __VA_ARGS__); \
box(log_box, 0, 0); \
wrefresh(log_box); \
wrefresh(log); } while (0)
#elif defined(VA_ARGS_CAT)
#define b_log(str, ...) do { \
scroll(log); \
mvwprintw(log, 11, 0, str, ##__VA_ARGS__); \
box(log_box, 0, 0); \
wrefresh(log_box); \
wrefresh(log); } while (0)
#else

#define EXPAND(x) x

// Don't put to many arguments I guess
#define GETNAME(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, \
_12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, \
_23, _24, _25, _26, _27, _28, _29, _30, NAME, ...) NAME

#define b_log(...) GETNAME(__VA_ARGS__, b_log2, b_log2, b_log2, b_log2, b_log2, \
b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, \
b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, b_log2, \
b_log2, b_log2, b_log2, b_log2, b_log1)(__VA_ARGS__)

#define b_log1(str) do { \
scroll(log); \
mvwprintw(log, 11, 0, str); \
box(log_box, 0, 0); \
wrefresh(log_box); \
wrefresh(log); } while (0)

#define b_log2(str, ...) do { \
scroll(log); \
mvwprintw(log, 11, 0, str, __VA_ARGS__); \
box(log_box, 0, 0); \
wrefresh(log_box); \
wrefresh(log); } while (0)
#endif


int main (int argc, char* argv[]) {
	initscr();
#ifdef HAVE_CURSES_COLOR
	if (has_colors() == TRUE) start_color();
#endif
	raw();
	noecho();
	scrollok(stdscr, FALSE);
	curs_set(0);
	timeout(-1);
	WINDOW* log_box = newwin(14, 32, 0, 40);
	WINDOW* log = newwin(12, 30, 1, 41);
	scrollok(log, TRUE);
	wclear(log);
	box(log_box, '|', '-');
	wrefresh(log_box);

	// Health, attack, defense, speed
	Player you("Player", 20, 5, 8, 1, 20, 3, 9), them("Goblin", 20, 10, 4, 2, 20, 0, 9);

	int ch = 0;

	// Battle timer
	mvaddstr(3, 0, "|           |");
	refresh();
	wait_for(std::chrono::milliseconds(500));
	mvaddch(3, 1, '-');
	mvaddch(3, 11, '-');
	refresh();
	wait_for(std::chrono::milliseconds(500));
	mvaddch(3, 2, '-');
	mvaddch(3, 10, '-');
	refresh();
	wait_for(std::chrono::milliseconds(500));
	mvaddch(3, 3, '-');
	mvaddch(3, 9, '-');
	refresh();
	wait_for(std::chrono::milliseconds(500));
	mvaddstr(3, 4, "Start");
	refresh();
	wait_for(std::chrono::milliseconds(500));

	getch();
	erase();
	mvaddstr(0, 0, "them:");
	mvaddstr(1, 0, "Health");
	mvprintw(3, 0, "you:");
	mvprintw(4, 0, "Health", you.health());
	mvprintw(6, 0, "Actions:");
	mvprintw(7, 0, "a - Attack");
	mvprintw(8, 0, "h - Heal");
	mvprintw(9, 0, "d - Defend");
	refresh();
	them.healthbar.disp();
	you.healthbar.disp();
	b_log("Begin battle.");
	int turn = you.speed() > them.speed();
	wait_for(std::chrono::seconds(1));
	while (ch != 'q' && ch != CTRL('c') && you.health() * them.health() > 0) {
		if (turn) {
			flushinp();
			ch = tolower(getch()); if (ch == 'q' || ch == CTRL('c')) break;
			you.unblock();
			switch (ch) {
			case 'a':
				b_log("%s takes %d damage.", them.name(), you.hit(them));
				break;
			case 'h':
				b_log("%s heals %d damage.", you.name(), you.heal(5));
				break;
			case 'd':
				b_log("%s blocks.", you.name());
				you.block();
				break;
			default:
				// If user specifies a non-action key, stay your turn.
				turn = !turn;
			}
		} else {
			b_log("%s takes %d damage.", you.name(), them.hit(you));
		}
		turn = !turn;
		wait_for(std::chrono::milliseconds(350));
	}
	timeout(-1);
	if (you.health() * them.health() <= 0)
		b_log("%s dies.", you.health() <= 0 ? you.name() : them.name());
	else
		b_log("For some reason you quit.");
	getch();
	endwin();
	delwin(log);
	delwin(log_box);
	return 0;
}
