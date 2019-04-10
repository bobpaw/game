#!/bin/sh

$(test -x '../src/test_app' && printf '.' || dirname $0)/../src/test_app
