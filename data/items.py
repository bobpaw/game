import json

item_count = 0

def h_ify(thing):
	if type(thing) == int:
		return thing
	possible_things = {
		"Weapon": "CLASS_WEAPON",
		"Armor": "CLASS_ARMOR",
		"Holdable": "CLASS_HOLD",
		"Fists": "WPN_TYPE_FISTS",
		"One-handed": "WPN_TYPE_ONEHAND",
		"HP": "HLD_TYPE_HP"
	}
	possible_things.update({n: "ARM_TYPE_" + n.upper() for n in ["Hand", "Chest", "Legs", "Feet", "Head", "Shield", "All"]})
	try:
		return possible_things[thing]
	except KeyError:
		return '"' + thing + '"'
	return None

def item(class_name, type_name, name, power):
	global item_count
	retval = {}
	retval["id"] = item_count
	item_count += 1
	retval["class"] = class_name
	retval["type"] = type_name
	retval["name"] = name
	retval["power"] = power
	return retval

with open("items.json", "r") as f:
	itemlist = json.load(f)
	item_count = len(itemlist)

def gen_h_file(itemlist, f):
	"""Generate a C header file (for this project) where f is a file-like
	object and itemlist is a list of dict's like ones returned by item()"""
	# I really want them in this order
	prop_order = ["id", "class", "type", "name", "power"]
	print('#include "item.h"', file=f)
	print("", file=f)
	print('#ifndef GAME_ITEMLIST_H_', file=f)
	print('#define GAME_ITEMLIST_H_', file=f)
	print("", file=f)
	print("const item_t item_list[] = {", file=f)
	for i, item in enumerate(itemlist):
		print("\t{", file=f)
		for e, entry in enumerate(prop_order):
			print("\t\t." + entry + " =", str(h_ify(item[entry])) + ("," if e != len(prop_order) - 1 else ""), file=f)
		print("\t}," if i != len(itemlist) - 1 else "}", file=f)
	print("};", file=f)
	print("", file=f)
	print("const uint16_t item_count = " + str(len(itemlist)) + ";", file=f)
	print("#endif // GAME_ITEMLIST_H_", file=f)
