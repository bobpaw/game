#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([game], [0], [aiden.woodruff@gmail.com])
AC_CONFIG_AUX_DIR([.])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE
AC_LANG([C++])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CXXCPP
AX_CXX_COMPILE_STDCXX([14], [noext], [optional])
if test $HAVE_CXX14 -eq 0; then
AX_CXX_COMPILE_STDCXX([11], [noext], [mandatory])
fi

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lncurses':
AX_WITH_CURSES

# Checks for header files.
AC_CHECK_HEADERS([string cstdint iostream functional random])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_UINT8_T
AC_TYPE_UINT16_T

# Checks for library functions.

AC_CONFIG_FILES([Makefile src/Makefile test/Makefile])
AC_OUTPUT
