#include "health_bar.h"

namespace game {
	// Update new health and display (assuming no changes)
	void HealthBar::update (int h) {
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
	void HealthBar::disp () {
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
}
