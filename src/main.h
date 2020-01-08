#include "config.h"

// C standard libraries
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <ctype.h>

// Module Libraries
#ifdef HAVE_CURSESW
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

// Project libraries
#include <item.h>
#include <monster.h>
#include <player.h>
#include <data/itemlist.h>
