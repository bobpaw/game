/*
	A simple 2D RPG using ncurses
	Copyright (C) 2019 Aiden Woodruff

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#include "main.h"

#ifndef CTRL
#define CTRL(x) ((x) & 037)
#endif

int main (int argc, char * argv[]) {
	char max_letter = argc == 2 ? argv[1][0] : 'm';
	int invent_used = max_letter + 1 - 'a';
	int ch = 0, och = 0;
	int width = 36, height = 18;
	int chance = 40, uchance = 5, dchance = -10;

	int drill = 3;
	char * invent = new char[invent_used]();
	int me = '@';

	try { // Catch-all to ensure window is ended
		// Default chance is 40 for a wall
		// Increases if the nearest are also walls
		// Meaning: better chance for large chunks of wall
		game::Application app(width, height, [chance, uchance, dchance](game::board* her, int x, int y, int rnd) {
			return (rnd % 100 < chance +
			(her->in_range(x - 1, y) && her->operator()(x - 1, y) == '#' ? uchance : dchance) +
			(her->in_range(x, y - 1) && her->operator()(x, y - 1) == '#' ? uchance : dchance)) ?
			'#' : '.';
		});

		auto engine = std::default_random_engine(std::random_device()());
		auto distribution = std::uniform_int_distribution<int>(0);
		for (int i = 'a', r = 0; i < max_letter + 1;) {
			r = distribution(engine) % (app.height() * app.width());
			if (app[r] == '.') app[r] = i++;
		}
		initscr();
		raw();
		scrollok(stdscr, FALSE);
		curs_set(0);
		keypad(stdscr, TRUE);
		noecho();
		for (int y = 0; y < app.height(); ++y)
			for (int x = 0; x < app.width(); ++x)
			mvaddch(y, x, app(x, y));
		mvprintw(0, app.width() + 1, "Drills: %d", drill);
		refresh();
		// int x = 3, y = 3;
		while (ch != 'q' && ch != CTRL('c')) {
			move(app.y, app.x);
			switch (ch) {
			case KEY_UP:
			case 'k':
				app.move(app.N);
#ifdef HAVE_NCURSESW
				me = ACS_UARROW;
#else
				me = '^';
#endif
				ch = KEY_UP;
				break;
			case KEY_DOWN:
			case 'j':
				app.move(app.S);
#ifdef HAVE_NCURSESW
				me = ACS_DARROW;
#else
				me = 'v';
#endif
				ch = KEY_DOWN;
				break;
			case KEY_LEFT:
			case 'h':
				app.move(app.W);
#ifdef HAVE_NCURSESW
				me = ACS_LARROW;
#else
				me = '<';
#endif
				ch = KEY_LEFT;
				break;
			case KEY_RIGHT:
			case 'l':
				app.move(app.E);
#ifdef HAVE_NCURSESW
				me = ACS_RARROW;
#else
				me = '>';
#endif
				ch = KEY_RIGHT;
				break;
			case KEY_A1:
			case 'y':
				switch (app.move(app.NW)) {
				case app.NW:
					echochar('\\');
					break;
				case app.N:
					echochar(ACS_VLINE);
					break;
				case app.W:
					echochar(ACS_HLINE);
					break;
				default:;
				}
				break;
			case KEY_A3:
			case 'u':
				switch (app.move(app.NE)) {
				case app.NE:
					echochar('/');
					break;
				case app.N:
					echochar(ACS_VLINE);
					break;
				case app.E:
					echochar(ACS_HLINE);
					break;
				default:;
				}
				break;
			case KEY_C1:
			case 'b':
				switch (app.move(app.SW)) {
				case app.SW:
					echochar('/');
					break;
				case app.S:
					echochar(ACS_VLINE);
					break;
				case app.W:
					echochar(ACS_HLINE);
					break;
				default:;
				}
				break;
			case KEY_C3:
			case 'n':
				switch (app.move(app.SE)) {
				case app.SE:
					echochar('\\');
					break;
				case app.S:
					echochar(ACS_VLINE);
					break;
				case app.E:
					echochar(ACS_HLINE);
					break;
				default:;
				}
				break;
			case 'd':
				if (drill > 0) {
					switch (och) {
					case KEY_LEFT:
						if (!app.is_clear(app.W) && app.in_range(app.W)) {
							app.in_direction(app.W) = '.';
							move(app.y, app.x - 1); echochar('.');
							--drill;
							move(0, app.width() + 1 + 8); // 8 is length of 'Drills: '
							echochar(drill + '0');
						} break;
					case KEY_RIGHT:
						if (!app.is_clear(app.E) && app.in_range(app.W)) {
							app.in_direction(app.E) = '.';
							move(app.y, app.x + 1); echochar('.');
							--drill;
							move(0, app.width() + 1 + 8); // 8 is length of 'Drills: '
							echochar(drill + '0');
						} break;
					case KEY_UP:
						if (!app.is_clear(app.N) && app.in_range(app.W)) {
							app.in_direction(app.N) = '.';
							move(app.y - 1, app.x); echochar('.');
							--drill;
							move(0, app.width() + 1 + 8); // 8 is length of 'Drills: '
							echochar(drill + '0');
						} break;
					case KEY_DOWN:
						if (!app.is_clear(app.S) && app.in_range(app.W)) {
							app.in_direction(app.S) = '.';
							move(app.y + 1, app.x); echochar('.');
							--drill;
							move(0, app.width() + 1 + 8); // 8 is length of 'Drills: '
							echochar(drill + '0');
						} break;
					}
				}
				break;
				case 'c':
					for (int y = 0; y < app.height(); ++y)
						for (int x = 0; x < app.width(); ++x)
							mvaddch(y, x, app(x, y));
					mvprintw(0, app.width() + 1, "Drills: %d", drill);
					for (int i = 0; i < max_letter - 'a'; ++i)
						mvaddch(app.height(), i, invent[i] != 0 ? invent[i] : ' ');
					refresh();
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
			move(app.y, app.x);
			echochar(me);
			if (app.here() >= 'a' && app.here() <= max_letter) {
				int letter = app.here();
				move(app.height(), letter - 'a');
				echochar(letter);
				invent[letter - 'a'] = letter;
				app.here() = '.';
				--invent_used;
			}
			if (invent_used == 0) {
				mvaddstr(app.height() + 1, 0, "Done!");
				refresh();
			}
			ch = tolower(getch());
		}
	} catch (const std::exception &e) {
		if (!isendwin()) endwin();
		std::cerr << "Something went wrong:\n" << e.what() << std::endl;
	}
	endwin();
	delete[] invent;
	exit(EXIT_SUCCESS);
}
