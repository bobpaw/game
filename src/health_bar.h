#include <stdexcept>
#include "correct_curses.h"

#ifndef GAME_HEALTH_BAR_H_
#define GAME_HEALTH_BAR_H_

namespace game {
	class HealthBar {
		WINDOW *win;
		int max_health_;
		int cur_health_;
		int border_ch[8];
		bool has_color;
		short pairs[3];
	public:

		decltype(max_health_) max_health () const { return max_health_; }

		HealthBar (int ul_y, int ul_x, int max, WINDOW *supwin = stdscr,
		int b0 = 0, int b1 = 0, int b2 = 0, int b3 = 0,
		int b4 = 0, int b5 = 0, int b6 = 0, int b7 = 0):
			max_health_(max), cur_health_(max), border_ch{ b0, b1, b2, b3, b4, b5, b6, b7 }, has_color{ false } {
			if (ul_y < 0 || ul_x < 0 || max < 0 || supwin == nullptr)
				throw std::invalid_argument("HealthBar constructor: invalid argument");
			win = supwin == stdscr ? newwin(3, max + 2, ul_y, ul_x) :
			derwin(supwin, 3, max + 2, ul_y, ul_x);
			pairs[0] = pairs[1] = pairs[2] = 0;
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

		// Update health & display
		void update (int h) noexcept;

		// Redraw
		void disp () noexcept;

		 ~HealthBar () {
			delwin(win);
		}

	};
}

#endif // GAME_HEALTH_BAR_H_
