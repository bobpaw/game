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
	for (int i = 'a', r = 0; i < 'n';) {
		r = rand() % (height * width);
		if (map[r] == '.') map[r] = i++;
	}
	int x = 3;
	int y = 3;
	int drills = 3;
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
		case 'k':
			if (y > 0 && base_map[y * width - width + x] == '.') y--;
			me = '^';
			ch = KEY_UP;
			break;
		case KEY_DOWN:
		case 'j':
			if (y < height - 1 && base_map[y * width + width + x] == '.') y++;
			me = 'v';
			ch = KEY_DOWN;
			break;
		case KEY_LEFT:
		case 'h':
			if (x > 0 && base_map[y * width + x - 1] == '.') x--;
			me = '<';
			ch = KEY_LEFT;
			break;
		case KEY_RIGHT:
		case 'l':
			if (x < width - 1 && base_map[y * width + x + 1] == '.') x++;
			me = '>';
			ch = KEY_RIGHT;
			break;
		case KEY_A1:
		case 'y':
			if (x > 0 && y > 0 && base_map[y * width - width + x - 1] == '.') {
				--x;
				--y;
				echochar('\\');
			} else if (x > 0 && base_map[y * width + x - 1] == '.') {
				--x;
				echochar(ACS_HLINE);
			} else if (y > 0 && base_map[y * width - width + x] == '.') {
				--y;
				echochar(ACS_VLINE);
			}
			break;
		case KEY_A3:
		case 'u':
			if (x < width - 1 && y > 0 && base_map[y * width - width + x + 1] == '.') {
				--y;
				++x;
				echochar('/');
			} else if (x < width - 1 && base_map[y * width + x + 1] == '.') {
				++x;
				echochar(ACS_HLINE);
			} else if (y > 0 && base_map[y * width - width] == '.') {
				y--;
				echochar(ACS_VLINE);
			}
			break;
		case KEY_C1:
		case 'b':
			if (x > 0 && y < height - 1 && base_map[y * width + width + x - 1] == '.') {
				--x;
				++y;
				echochar('/');
			} else if (x > 0 && base_map[y * width + x - 1] == '.') {
				--x;
				echochar(ACS_HLINE);
			} else if (y < height - 1 && base_map[y * width + width + x] == '.') {
				++y;
				echochar(ACS_VLINE);
			}
			break;
		case KEY_C3:
		case 'n':
			if (x < width - 1 && y < height - 1 && base_map[y * width + width + x + 1] == '.') {
				++x;
				++y;
				echochar('\\');
			} else if (x < width - 1 && base_map[y * width + x + 1] == '.') {
				++x;
				echochar(ACS_HLINE);
			} else if (y < height - 1 && base_map[y * width + width + x] == '.') {
				++y;
				echochar(ACS_VLINE);
			}
			break;
		case 'd':
			if (drill > 0) {
				// drill a hole, based off och
			}
		}
		switch (ch) {
			case KEY_DOWN: // & 255 == 2
			case KEY_UP: // & 255 == 3
			case KEY_LEFT: // & 255 == 4
			case KEY_RIGHT: // & 255 == 5
			och &= 255;
			ch &= 255;
			if (och == ch) {
				echochar((ch & 2) == 2 ? ACS_VLINE : ACS_HLINE);
			} else if (och + ch == 5) {
				echochar(ACS_VLINE);
			} else if (och + ch == 9) {
				echochar(ACS_HLINE);
			} else if (och + ch == 7) {
				echochar((och == 3 || och == 4) != ((ch & 2) == 2) ? ACS_URCORNER : ACS_LLCORNER);
			} else {
				echochar((och + ch == 8) != ((ch & 2) == 2) ? ACS_ULCORNER : ACS_LRCORNER);
			}
			ch |= 256;
			och = ch;
		}
		move(y, x);
		echochar(me);
		if (map[width * y + x] != '.') {
			move(height, map[width * y + x]- 'a');
			echochar(map[width * y + x]);
			map[width * y + x] = '.';
		}
		ch = tolower(getch());
		refresh();
	}
	endwin();
	free(base_map);
	free(map);
	free(invent_item_count);
	exit(EXIT_SUCCESS);
}
