AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game battle
AM_CPPFLAGS = -Wall -Wextra -pedantic
battle_SOURCES = battle.cc health_bar.cc health_bar.h stats.h correct_curses.h
battle_LDADD = $(CURSES_LIBS)
battle_CXXFLAGS = $(CURSES_CFLAGS)

game_SOURCES = main.cc main.h app.cc app.h board.h item.h monster.h player.h data/itemlist.h correct_curses.h
game_LDADD = $(CURSES_LIBS)
game_CXXFLAGS = $(CURSES_CFLAGS)
EXTRA_DIST = data/items.json data/items.py

check_PROGRAMS = test_board test_app
test_board_SOURCES = test_board.cc board.h correct_curses.h
test_app_SOURCES = test_app.cc app.cc app.h correct_curses.h

data/itemlist.h: data/items.json data/items.py
	data/items.py --build

maintainer-clean-local:
	rm -f $(srcdir)/*~ $(srcdir)/\#*#
