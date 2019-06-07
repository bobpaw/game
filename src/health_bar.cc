#include "health_bar.h"

namespace game {
	// Update new health and display
	void HealthBar::update (int h) {
		if (h < 0 || h > max_health_) return;
#ifdef HAVE_CURSES_COLOR
		if (has_color) {
			if (h <= max_health_ / 10)
				wattron(win, COLOR_PAIR(pairs[2]));
			else if (h <= max_health_ / 2)
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
		mvwhline(win, 1, h + 1, ' ', max_health_ - h);
		cur_health_ = h;
		wrefresh(win);
	}

	// Redraw
	void HealthBar::disp () {
		wborder(win, border_ch[0], border_ch[1], border_ch[2], border_ch[3], border_ch[4], border_ch[5], border_ch[6], border_ch[7]);
#ifdef HAVE_CURSES_COLOR
		if (has_color) {
			if (cur_health_ <= max_health_ / 10)
				wattron(win, COLOR_PAIR(pairs[2]));
			else if (cur_health_ <= max_health_ / 2)
				wattron(win, COLOR_PAIR(pairs[1]));
			else
				wattron(win, COLOR_PAIR(pairs[0]));
			mvwhline(win, 1, 1, '#', cur_health_);
			wattron(win, COLOR_PAIR(0));
		} else {
			mvwhline(win, 1, 1, '#', cur_health_);
		}
#else
		mvwhline(win, 1, 1, '#', cur_health_);
#endif
		mvwhline(win, 1, cur_health_ + 1, ' ', max_health_ - cur_health_);
		wrefresh(win);
	}
}
