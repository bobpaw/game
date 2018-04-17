SUBDIRS = life maze
ncurses_flags = `ncurses5-config --libs` `ncurses5-config --cflags`
libxml2_flags = `xml2-config --libs` `xml2-config --cflags`
cstd_flag = -std=c11
AUTOMAKE_OPTIONS = gnu
bin_PROGRAMS = game xml
game_SOURCES = main.c
include_HEADERS = item.h player.h monster.h main.h xml.h
EXTRA_DIST = items.xml
game_CFLAGS = $(ncurses_flags) $(libxml2_flags) $(cstd_flag)
xml_SOURCES = xml.c
xml_CFLAGS = $(libxml2_flags)
maintainer-clean-local:
	rm -f $(srcdir)/*~ $(srcdir)/\#*#
