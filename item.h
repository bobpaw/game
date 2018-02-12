#ifndef GAME_ITEMS_ITEM_H_
#define GAME_ITEMS_ITEM_H_

// Constants

// Classes
const char CLASS_WEAPON = 0;
const char CLASS_ARMOR = 1;
const char CLASS_HOLD = 2;

// Weapon Types
const char WPN_TYPE_FISTS = 0;
const char WPN_TYPE_ONEHANDED = 1;

// Armor Types
const char ARM_TYPE_HAND =  0x01;
const char ARM_TYPE_CHEST = 0x02;
const char ARM_TYPE_LEGS =  0x04;
const char ARM_TYPE_FEET =  0x08;
const char ARM_TYPE_HEAD =  0x10;
const char ARM_TYPE_ALL =   0x1F;

struct item_t {
  int id;
  char class;
  char type;
  char * name;
  int power;
}; // struct item

#endif // GAME_ITEMS_ITEM_H_
