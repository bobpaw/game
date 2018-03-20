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
  item_tPtr items = NULL;
  int invent_used = 0;
  int itemcount = 0;
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
  items = readxmlfile("items.xml", &itemcount);
  if (items == NULL) {
    exit(EXIT_FAILURE);
  }
  invent_item_count = calloc(itemcount, sizeof(int));
  initscr();
  raw();
  curs_set(0);
  keypad(stdscr, TRUE);
  noecho();
  while (ch != 'q') {
    erase();
    if (ch == KEY_UP) {
      if (y > 0) y--;
    } else if (ch == KEY_DOWN) {
      if (y < height - 1) y++;
    } else if (ch == KEY_LEFT) {
      if (x > 0) x--;
    } else if (ch == KEY_RIGHT) {
      if (x < width - 1) x++;
    } else if (ch == KEY_A1) {
      if (x > 0) x--;
      if (y > 0) y--;
    } else if (ch == KEY_A3) {
      if (x < width - 1) x++;
      if (y > 0) y--;
    } else if (ch == KEY_C1) {
      if (x > 0) x--;
      if (y < height - 1) y++;
    } else if (ch == KEY_C3) {
      if (x < width - 1) x++;
      if (y < height - 1) y++;
    }
    memcpy(map, base_map, height * width);
    map[y*width + x] = '@';
    for (int i = 0; i < height; ++i) {
      printw("%.*s\n", width, (map + (i * width)));
    }
    refresh();
    ch = getch();
  }
  endwin();
  free(base_map);
  free(map);
  for (int i = 0; i < itemcount; i++) {
    free(items[i].name);
  }
  free(items);
  free(invent_item_count);
  exit(EXIT_SUCCESS);
}
