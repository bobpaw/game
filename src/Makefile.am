AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game
game_SOURCES = main.cc main.h app.cc app.h board.h item.h monster.h player.h data/itemlist.h
game_LDADD = $(CURSES_LIBS)
game_CXXFLAGS = $(CURSES_CFLAGS)
EXTRA_DIST = data/items.json data/items.py
game_CPPFLAGS = -Wall -Wextra -pedantic

data/itemlist.h: data/items.json data/items.py
	data/items.py --build

maintainer-clean-local:
	rm -f $(srcdir)/*~ $(srcdir)/\#*#
