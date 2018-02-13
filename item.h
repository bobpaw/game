#ifndef GAME_ITEMS_ITEM_H_
#define GAME_ITEMS_ITEM_H_

// Constants

// Item Classes
enum CLASS {
  CLASS_WEAPON = 1,
  CLASS_ARMOR,
  CLASS_HOLD};
typedef enum CLASS CLASS;

// Weapon Types
const char WPN_TYPE_FISTS = 1;
const char WPN_TYPE_ONEHAND = 2;

// Armor Types
const char ARM_TYPE_HAND =  0x01;
const char ARM_TYPE_CHEST = 0x02;
const char ARM_TYPE_LEGS =  0x04;
const char ARM_TYPE_FEET =  0x08;
const char ARM_TYPE_HEAD =  0x10;
const char ARM_TYPE_ALL =   0x1F;

typedef struct item_t {
  int id;
  CLASS class;
  char type;
  char * name;
  int power;
} item_t, * item_tPtr;

#endif // GAME_ITEMS_ITEM_H_
