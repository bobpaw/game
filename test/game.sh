#!/bin/sh

echo -n 'q' | $(test -x '../src/game' && printf '.' || dirname $0)/../src/game
