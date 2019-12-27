#!/usr/bin/env sh

if [ "${TRAVIS_OS_NAME}" = "windows" ]; then
	wget https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.1.tar.gz
	tar zvxf ncurses-6.1.tar.gz
	cd ncurses-6.1
	./configure && make -j2
fi
