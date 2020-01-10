#!/usr/bin/env sh

set -e

##
## items.sh: Output (for debug) or build file itemlist.h from itemlist.h.in and items.json
##
## Requirements:
## jq
##
## Invocation:
## ./items.sh [--build]
##

which jq > /dev/null || exit 1

which mawk > /dev/null || alias mawk=awk

# Get an item count
item_count="$(jq 'length' $(dirname $0)/items.json)"

items=$(cat <<"EOF" | jq -r -f /dev/stdin $(dirname $0)/items.json | mawk -v item_count=$item_count 'NR != item_count {print($0 ",")} NR == item_count {print}')
.[] | {class: .class | rtrimstr("able") | ascii_downcase, type: .type | ascii_downcase | sub("one-handed"; "onehand"), name, power, id} | "\t\titem(\(.id), \(.class), \(.type), \"\(.name)\", \(.power))"
EOF

cat > $(echo "$*" | grep -qF -- '--build' && echo $(dirname $0)/itemlist.h || echo /dev/stdout) <<EOF
#include <array>

#include "item.h"

#ifndef GAME_ITEMLIST_H_
#define GAME_ITEMLIST_H_

namespace game {
	const std::array<item,$item_count> item_list = {
$items
	};

} // namespace game
#endif // GAME_ITEMLIST_H_
EOF
