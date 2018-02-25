SUBDIRS = life
AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game xml
game_SOURCES = main.c
include_HEADERS = item.h player.h monster.h main.h xml.h
EXTRA_DIST = items.xml
game_CFLAGS = -I/usr/include/libxml2 -lxml2 -lncurses
xml_SOURCES = xml.c
xml_CFLAGS = -I/usr/include/libxml2 -lxml2
maintainer-clean-local:
	rm -f \#*# *~
