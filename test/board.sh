#!/bin/sh

$(test -x '../src/test_board' && printf '.' || dirname $0)/../src/test_board
