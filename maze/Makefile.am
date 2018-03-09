AM_OPTIONS = gnu
bin_PROGRAMS = maze put
maze_SOURCES = maze.c
maze_CFLAGS = -lncurses -ltinfo -I$(srcdir)
put_SOURCES = put.c
put_CFLAGS = -lncurses -ltinfo -I$(srcdir)
include_HEADERS = maze.h shuffle.h
maintainer-clean-local:
	rm -f *~ \#*#
