/*
	A simple 2D RPG using ncurses
	Copyright (C) 2019 Aiden Woodruff

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// Include for int types
#include <cstdint>
#include <string>

#ifndef GAME_ITEM_H_
#define GAME_ITEM_H_

// Constants

namespace game {
	enum Class {
		weapon = 0,
		armor,
		hold
	};
	const std::string Class_str[] = {"Weapon", "Armor", "Holdable"};

// Weapon and Armor Types
	enum Type {
		fists = 0,
		onehand,
		hand,
		chest,
		legs,
		feet,
		head,
		shield,
		all,
		hp
	};
	const std::string Type_str[] = {"Fists", "One-handed", "Hand", "Chest", "Legs", "Feet", "Head", "Shield", "All", "HP"};

	class item {
	public:
		uint16_t id;
		Class clas;
		Type type;
		std::string name;
		uint8_t power;

		item (decltype(id) id_, decltype(clas) clas_, decltype(type) type_, decltype(name) name_, decltype(power) power_):
		id(id_), clas(clas_), type(type_), name(name_), power(power_) {}
	};
} // namespace game

#endif // GAME_ITEM_H_
