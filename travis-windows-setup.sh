#!/usr/bin/env sh

if [ "${TRAVIS_OS_NAME}" = "windows" ]; then
	choco install make
	wget -q https://ftp.gnu.org/pub/gnu/ncurses/ncurses-6.1.tar.gz
	tar zxf ncurses-6.1.tar.gz
	cd ncurses-6.1
	./configure --without-pkg-config && make -j2
fi
