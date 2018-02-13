AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game
game_SOURCES = main.c
include_HEADERS = main.h item.h player.h monster.h
EXTRA_DIST = items.xml
game_CFLAGS = $(xml2-config --cflags) $(xml2-config --libs)
