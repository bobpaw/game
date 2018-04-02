AM_OPTIONS = gnu
bin_PROGRAMS = maze put
maze_SOURCES = main.c
maze_CFLAGS = $(ncurses_flags) -I$(srcdir)
put_SOURCES = put.c
put_CFLAGS = -I$(srcdir)
include_HEADERS = maze.h shuffle.h main.h
maintainer-clean-local:
	rm -f *~ \#*#
