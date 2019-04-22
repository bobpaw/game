AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game battle
battle_SOURCES = battle.cc stats.h
battle_LDADD = $(CURSES_LIBS)
battle_CXXFLAGS = $(CURSES_CFLAGS)

game_SOURCES = main.cc main.h app.cc app.h board.h item.h monster.h player.h data/itemlist.h
game_LDADD = $(CURSES_LIBS)
game_CXXFLAGS = $(CURSES_CFLAGS)
EXTRA_DIST = data/items.json data/items.py

check_PROGRAMS = test_board test_app
test_board_SOURCES = test_board.cc board.h
test_app_SOURCES = test_app.cc app.cc app.h

data/itemlist.h: data/items.json data/items.py
	data/items.py --build

maintainer-clean-local:
	rm -f $(srcdir)/*~ $(srcdir)/\#*#
