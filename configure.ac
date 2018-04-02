#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([game], [1.0], [aiden.woodruff@gmail.com])
AC_CONFIG_AUX_DIR([.])
AC_CONFIG_SRCDIR([main.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lncurses':
AC_CHECK_LIB([ncurses], [refresh], [], [AC_MSG_ERROR([ncurses not found])])
# FIXME: Replace `main' with a function in `-lxml2':
AC_CHECK_LIB([xml2], [xmlFreeDoc], [], [AC_MSG_ERROR([xml2 not found])])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([memset])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_SUBDIRS([life maze])
AC_OUTPUT
