/*
	A simple 2D RPG using ncurses
	Copyright (C) 2018 Aiden Woodruff

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.	If not, see <http://www.gnu.org/licenses/>.
*/
#include "main.h"

int main (int argc, char * argv[]) {
	srand(clock());
	int invent_used = 0;
	int ch = 0, och = 0;
	int width = 36;
	int height = 18;
	char * base_map = NULL;
	base_map = malloc(height * width + 1);
	if (base_map == NULL) {
		fprintf(stderr, "Ran out of memory\n");
		exit(EXIT_FAILURE);
	}
	base_map[height * width] = 0;
	int chance = 40, uchance = 5, dchance = -10;
	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x) {
			// Default chance is 40 for a wall
			// Increases if the nearest are also walls
			// Meaning: better chance for large chunks of wall
			if (rand() % 100 < chance +
			(x > 0 && base_map[y * width + x - 1] == '#' ? uchance : dchance) +
			(y > 0 && base_map[y * width - width + x] == '#' ? uchance : dchance))
				base_map[y * width + x] = '#';
			else base_map[y * width + x] = '.';
		}
	char * map = NULL;
	map = malloc(height * width + 1);
	map[height * width] = 0;
	memcpy(map, base_map, height * width);
	int x = 3;
	int y = 3;
	int * invent_item_count = NULL;
	char me = '@';
	invent_item_count = calloc(item_count, sizeof(uint16_t));
	initscr();
	raw();
	scrollok(stdscr, FALSE);
	curs_set(0);
	keypad(stdscr, TRUE);
	noecho();
	for (int i = 0; i < height; ++i)
		mvprintw(i, 0, "%.*s", width, (map + (i * width)));
	while (ch != 'q') {
		move(y, x);
		switch (ch) {
		case KEY_UP:
			if (y > 0 && base_map[y * width - width + x] == '.') y--;
			me = '^';
			break;
		case KEY_DOWN:
			if (y < height - 1 && base_map[y * width + width + x] == '.') y++;
			me = 'v';
			break;
		case KEY_LEFT:
			if (x > 0 && base_map[y * width + x - 1] == '.') x--;
			me = '<';
			break;
		case KEY_RIGHT:
			if (x < width - 1 && base_map[y * width + x + 1] == '.') x++;
			me = '>';
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
		switch (och) {
		case KEY_UP:
			switch (ch) {
			case KEY_UP:
			case KEY_DOWN:
				echochar(ACS_VLINE);
				break;
			case KEY_RIGHT:
				echochar(ACS_ULCORNER);
				break;
			case KEY_LEFT:
				echochar(ACS_URCORNER);
				break;
			}
			break;
		case KEY_RIGHT:
			switch (ch) {
			case KEY_UP:
				echochar(ACS_LRCORNER);
				break;
			case KEY_RIGHT:
			case KEY_LEFT:
				echochar(ACS_HLINE);
				break;
			case KEY_DOWN:
				echochar(ACS_URCORNER);
				break;
			}
			break;
		case KEY_LEFT:
			switch (ch) {
			case KEY_UP:
				echochar(ACS_LLCORNER);
				break;
			case KEY_RIGHT:
			case KEY_LEFT:
				echochar(ACS_HLINE);
				break;
			case KEY_DOWN:
				echochar(ACS_ULCORNER);
				break;
			}
			break;
		case KEY_DOWN:
			switch (ch) {
			case KEY_RIGHT:
				echochar(ACS_LLCORNER);
				break;
			case KEY_LEFT:
				echochar(ACS_LRCORNER);
				break;
			case KEY_DOWN:
			case KEY_UP:
				echochar(ACS_VLINE);
				break;
			}
			break;
		}
		move(y, x);
		echochar(me);
		switch (ch) {
		case KEY_UP:
		case KEY_RIGHT:
		case KEY_LEFT:
		case KEY_DOWN:
			och = ch;
		}
		ch = getch();
		refresh();
	}
	endwin();
	free(base_map);
	free(map);
	free(invent_item_count);
	exit(EXIT_SUCCESS);
}
