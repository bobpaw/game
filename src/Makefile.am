AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game
game_SOURCES = main.c main.h item.h monster.h player.h data/itemlist.h
EXTRA_DIST = data/items.json data/items.py
game_CPPFLAGS = -Wall -Wextra -pedantic

data/itemlist.h: data/items.json data/items.py
	data/items.py --build

maintainer-clean-local:
	rm -f $(srcdir)/*~ $(srcdir)/\#*#
