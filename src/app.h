#include <functional> // std::function

#include "game_map.h"

#ifndef GAME_APP_H_
#define GAME_APP_H_

namespace game {
	class Application {
	private:
		game_map map;

	public:
		int x, y;

		Application (int width, int height, std::function<char(game_map*, int, int, int)> a = nullptr): map(width, height, a), x(3), y(3) {}

		auto width () const noexcept { return map.width(); }
		auto height () const noexcept { return map.height(); }

		char &operator() (int x, int y) { return map(x, y); }
		char operator() (int x, int y) const { return map(x, y); }

		char &operator[] (int n) { return map[n]; }
		char operator[] (int n) const { return map[n]; }

		enum direction {none = 0, N, E, S, W, NE, SE, SW, NW};

		bool in_range (direction d) const noexcept;
		char &in_direction (direction d);
		char in_direction (direction d) const;

		char &here () { return in_direction(none); }
		char here () const { return in_direction(none); }

		bool is_clear (direction d) const noexcept {
			return in_range(d) && in_direction(d) != '#';
		}

		direction move (direction d);

	};

} // namespace game

#endif // GAME_APP_H_
