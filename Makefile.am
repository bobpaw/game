AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game xml life
game_SOURCES = main.c main.h
include_HEADERS = item.h player.h monster.h
EXTRA_DIST = items.xml
game_CFLAGS = -I/usr/include/libxml2 -lxml2 -lncurses
xml_SOURCES = xml.c xml.h
xml_CFLAGS = -I/usr/include/libxml2 -lxml2
life_SOURCES = life.c life.h
life_CFLAGS = -lncurses
maintainer-clean-local:
	rm -f \#*# *~
