AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game xml life
game_SOURCES = main.c
include_HEADERS = item.h player.h monster.h cmdline-life.h main.h xml.h life.h
EXTRA_DIST = items.xml
game_CFLAGS = -I/usr/include/libxml2 -lxml2 -lncurses
xml_SOURCES = xml.c
xml_CFLAGS = -I/usr/include/libxml2 -lxml2
life_SOURCES = life.c cmdline-life.c
life_CFLAGS = -lncurses
maintainer-clean-local:
	rm -f \#*# *~
