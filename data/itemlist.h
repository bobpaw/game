#include "item.h"

#ifndef GAME_ITEMLIST_H_
#define GAME_ITEMLIST_H_

const item_t item_list[] = {
  {
    .id = 0,
    .class = CLASS_WEAPON,
    .type = WPN_TYPE_FISTS,
    .name = "Unarmed",
    .power = 1
  },
  {
    .id = 1,
    .class = CLASS_ARMOR,
    .type = ARM_TYPE_ALL,
    .name = "Bare",
    .power = 0
  },
  {
    .id = 2,
    .class = CLASS_WEAPON,
    .type = WPN_TYPE_ONEHAND,
    .name = "Dagger",
    .power = 2
  },
  {
    .id = 3,
    .class = CLASS_ARMOR,
    .type = ARM_TYPE_CHEST,
    .name = "Tunic",
    .power = 1
  },
  {
    .id = 4,
    .class = CLASS_HOLD,
    .type = HLD_TYPE_HP,
    .name = "Level 1 Potion",
    .power = 1
  },
  {
    .id = 5,
    .class = CLASS_ARMOR,
    .type = ARM_TYPE_SHIELD,
    .name = "Leather Shield",
    .power = 2
  },
  {
    .id = 6,
    .class = CLASS_WEAPON,
    .type = WPN_TYPE_ONEHAND,
    .name = "Short Sword",
    .power = 3
  }
};

const uint16_t item_count = 7;
#endif // GAME_ITEMLIST_H_
