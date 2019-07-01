#!/usr/bin/env python3

import json
import sys

item_count = 0

def h_ify(thing):
	if type(thing) == int:
		return thing
	possible_things = {
		"Weapon": "weapon",
		"Armor": "armor",
		"Holdable": "hold",
		"Fists": "fists",
		"One-handed": "onehand",
		"HP": "hp"
	}
	possible_things.update({n: n.lower() for n in ["Hand", "Chest", "Legs", "Feet", "Head", "Shield", "All"]})
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

with open(sys.argv[0][:-2] + "json", "r") as f:
	itemlist = json.load(f)
	item_count = len(itemlist)

def gen_h_file(itemlist, f):
	"""Generate a C header file (for this project) where f is a file-like
	object and itemlist is a list of dict's like ones returned by item()"""
	# I really want them in this order
	prop_order = ["id", "class", "type", "name", "power"]
	print("""#include <array>

#include \"item.h\"

#ifndef GAME_ITEMLIST_H_
#define GAME_ITEMLIST_H_

namespace game {"""
	, file=f)
	print("\tconst std::array<item,{}> item_list = {{".format(len(itemlist)), file=f)
	for i, item in enumerate(itemlist):
		print("\t\titem(", file=f, end="")
		for e, entry in enumerate(prop_order):
			print(str(h_ify(item[entry])) + ("," if e != len(prop_order) - 1 else ""), file=f, end="")
		print(")," if i != len(itemlist) - 1 else ")", file=f)
	print("\t};", file=f)
	print("", file=f)
	print("} // namespace game", file=f)
	print("#endif // GAME_ITEMLIST_H_", file=f)

if "--build" in sys.argv:
	with open(sys.argv[0][:-4] + "list.h", "w") as f:
		gen_h_file(itemlist, f)
