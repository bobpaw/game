/*
    A simple 2D RPG using ncurses
    Copyright (C) 2018 Aiden Woodruff

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Include for int types
#include <stdint.h>

#ifndef GAME_ITEM_H_
#define GAME_ITEM_H_
#define TYPE_COUNT 10

// Constants

// Item Classes
enum CLASS {
  CLASS_WEAPON = 1,
  CLASS_ARMOR,
  CLASS_HOLD};
typedef enum CLASS CLASS;
const char * CLASS_STR[3] = {"Weapon", "Armor", "Holdable"};

// Weapon and Armor Types
enum TYPE {
  WPN_TYPE_FISTS = 1,
  WPN_TYPE_ONEHAND,
  ARM_TYPE_HAND,
  ARM_TYPE_CHEST,
  ARM_TYPE_LEGS,
  ARM_TYPE_FEET,
  ARM_TYPE_HEAD,
  ARM_TYPE_SHIELD,
  ARM_TYPE_ALL,
  HLD_TYPE_HP};
typedef enum TYPE TYPE;

const char * TYPE_STR[TYPE_COUNT] = {"Fists", "One-handed", "Hand", "Chest", "Legs", "Feet", "Head", "Shield", "All", "HP"};

typedef struct item_t {
  uint16_t id;
  CLASS class;
  TYPE type;
  char * name;
  uint8_t power;
} item_t, * item_tPtr;
#endif // GAME_ITEM_H_
