#include "correct_curses.h"

#ifndef GAME_HEALTH_BAR_H_
#define GAME_HEALTH_BAR_H_

namespace game {
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

    void update (int h);
    void disp ();

 	  ~HealthBar () {
		  delwin(win);
	  }

  };
}

#endif // GAME_HEALTH_BAR_H_
