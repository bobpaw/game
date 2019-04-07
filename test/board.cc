#include <iostream>
#include <src/board.h>

int main () {
	std::cout << "width, height constructor" << std::endl;
	game::board map(10, 10);
	std::cout << "copy constructor" << std::endl;
	game::board copy_con(map);
	std::cout << "copy assignment" << std::endl;
	game::board copy_asn(1, 1);
	copy_asn = map;
	std::cout << "move constructor" << std::endl;
	game::board move_con(std::move(copy_con));
	std::cout << "move assignment" << std::endl;
	game::board move_asn(1, 1);
	move_asn = std::move(copy_asn);
	std::cout << "function constructor" << std::endl;
	game::board map2(10, 5, [](game::board *, int, int, int rnd) {
		return rnd % 26 + 'a';
	});
	std::cout << "fill constructor" << std::endl;
	game::board map7(10, 10, 'f');

	std::cout << "operator()" << std::endl;
	if (map2(2, 2) > 'z' || map2(2, 2) < 'a') return -1;

	std::cout << "operator() assignment" << std::endl;
	map7(3, 4) = 'g';

	std::cout << "in_range()" << std::endl;
	if (!move_asn.in_range(2, 5)) return -1;
	for (int y = 0; y < map7.height(); ++y) {
		for (int x = 0; x < map7.width(); ++x)
			std::cout << map7(x, y);
		std::cout << '\n';
	}
	std::cout << std::flush;
	return 0;
}
