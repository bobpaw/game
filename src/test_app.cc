#include <iostream>
#include "app.h"

int main () {
	game::Application app(10, 10, [](game::board*, int, int, int) { return '.'; });
	std::cout << "Width: " << app.width() << std::endl;
	std::cout << "Height: " << app.height() << std::endl;
	std::cout << "operator() access: " << app(3, 2) << std::endl;
	std::cout << "operator() modify (3, 2) to f" << std::endl;
	app(3, 2) = 'f';
	std::cout << "operator[] access: " << app[16] << std::endl;
	std::cout << "operator[] modify [16] to b" << std::endl;
	app[16] = 'b';
	std::cout << "in_range: " << std::boolalpha << app.in_range(app.W) << std::endl;
	std::cout << "in_direction: (3, 4) " << app.in_direction(app.S) << std::endl;
	std::cout << "in_direction modify (3, 4) to q" << std::endl;
	app.in_direction(app.S) = 'q';
	std::cout << "here access: " << app.here() << std::endl;
	std::cout << "here modify: (3, 3) to z" << std::endl;
	app.here() = 'z';
	std::cout << "is_clear: (4, 4) " << app.is_clear(app.SE) << std::endl;
	std::cout << "move (4, 3)" << std::endl;
	app.move(app.E);
	std::cout << "here modify (4, 3) to y" << std::endl;
	app.here() = 'y';
	for (int y = 0; y < app.height(); ++y) {
		for (int x = 0; x < app.width(); ++x)
			std::cout << app(x, y);
		std::cout << '\n';
	}
	std::cout << std::flush;
	return 0;
}
