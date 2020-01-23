find_path(PDCURSES_INCLUDE_DIR curses.h)
find_library(PDCURSES_LIBRARY pdcurses)

file(STRINGS "${PDCURSES_INCLUDE_DIR}/curses.h" _PDCURSES_VERSION_STR REGEX "^#define PDC_VERDOT[ \t]+\\\".*\\\"$")

string(REGEX REPLACE "^#define PDC_VERDOT[ \t]+\\\"\\(.*\\)\\\"$" "\\1" PDCURSES_VERSION "${_PDCURSES_VERSION_STR}")

set(PDCURSES_LIBRARIES ${PDCURSES_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
PDCurses
REQUIRED_VARS
  PDCURSES_LIBRARY
  PDCURSES_INCLUDE_DIR
VERSION_VAR PDCURSES_VERSION)

set(HAVE_CURSES_H TRUE)

mark_as_advanced(PDCURSES_LIBRARY PDCURSES_LIBRARIES PDCURSES_INCLUDE_DIR PDCURSES_VERSION)