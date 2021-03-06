#if defined(HAVE_CONFIG_H)
#include <config.h>
#elif defined(HAVE_CMAKECONFIG_H)
#include <cmakeconfig.h>
#endif

// C++ standard libraries
// #include <string>
#include <cstdint>
#include <cctype>
#include <random>
#include <iostream>
#include <stdexcept>

// Module Libraries
#include "correct_curses.h"

// Project libraries
#include <item.h>
#include <data/itemlist.h>
#include <monster.h>
#include <player.h>
#include <app.h>
#include <board.h>
