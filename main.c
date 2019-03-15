/*
    A simple 2D RPG using ncurses
    Copyright (C) 2018 Aiden Woodruff

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "main.h"

int main (int argc, char * argv[]) {
  srand(time(NULL));
  int invent_used = 0;
  int ch = 0;
  int width = 36;
  int height = 18;
  char * base_map = NULL;
  base_map = malloc(height * width+1);
  if (base_map == NULL) {
    fprintf(stderr, "Ran out of memory\n");
    exit(EXIT_FAILURE);
  }
  memset(base_map, 0, height * width + 1);
  memset(base_map, '.', height * width);
  char * map = NULL;
  map = malloc(height * width+1);
  memset(map, 0, height * width + 1);
  memcpy(map, base_map, height * width);
  int x = 3;
  int y = 3;
  int * invent_item_count = NULL;
  invent_item_count = calloc(item_count, sizeof(uint16_t));
  initscr();
  raw();
  scrollok(stdscr, FALSE);
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  while (ch != 'q') {
   // clear();
    switch (ch) {
    case KEY_UP:
      if (y > 0) y--;
      break;
    case KEY_DOWN:
      if (y < height - 1) y++;
      break;
    case KEY_LEFT:
      if (x > 0) x--;
      break;
    case KEY_RIGHT:
      if (x < width - 1) x++;
      break;
    case KEY_A1:
      if (x > 0) x--;
      if (y > 0) y--;
      break;
    case KEY_A3:
      if (x < width - 1) x++;
      if (y > 0) y--;
      break;
    case KEY_C1:
      if (x > 0) x--;
      if (y < height - 1) y++;
      break;
    case KEY_C3:
      if (x < width - 1) x++;
      if (y < height - 1) y++;
      break;
    }
    //memcpy(map, base_map, height * width);
    for (int i = 0; i < height; ++i) {
      mvprintw(i, 0, "%.*s\n", width, (map + (i * width)));
    }
    mvaddch(y, x, '@');
    ch = getch();
    refresh();
  }
  endwin();
  free(base_map);
  free(map);
  free(invent_item_count);
  exit(EXIT_SUCCESS);
}
