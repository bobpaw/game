#include <array>

#include "item.h"

#ifndef GAME_ITEMLIST_H_
#define GAME_ITEMLIST_H_

namespace game {
	const std::array<item,7> item_list = {
		item(0,weapon,fists,"Unarmed",1),
		item(1,armor,all,"Bare",0),
		item(2,weapon,onehand,"Dagger",2),
		item(3,armor,chest,"Tunic",1),
		item(4,hold,hp,"Level 1 Potion",1),
		item(5,armor,shield,"Leather Shield",2),
		item(6,weapon,onehand,"Short Sword",3)
	};

} // namespace game
#endif // GAME_ITEMLIST_H_
