#ifndef GAME_ITEMS_ITEM_H_
#define GAME_ITEMS_ITEM_H_
#define TYPE_COUNT 9

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
  ARM_TYPE_ALL,
  HLD_TYPE_HP};
typedef enum TYPE TYPE;

const char * TYPE_STR[TYPE_COUNT] = {"Fists", "One-handed", "Hand", "Chest", "Legs", "Feet", "Head", "All", "HP"};

typedef struct item_t {
  int id;
  CLASS class;
  TYPE type;
  char * name;
  int power;
} item_t, * item_tPtr;

#endif // GAME_ITEMS_ITEM_H_
