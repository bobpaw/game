#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <functional> // std::function

#include "board.h"

#ifndef GAME_APP_H_
#define GAME_APP_H_

namespace game {
	class Application {
	private:
		board map;
		using chartype = board::chartype;

	public:
		int x, y;

		Application (int width, int height, std::function<char(board*, int, int, int)> a = nullptr): map(width, height, a), x(3), y(3) {}

#ifdef HAVE_CXX14
		auto width () const noexcept { return map.width(); }
		auto height () const noexcept { return map.height(); }
#else
		auto width () const noexcept -> decltype(map.width()) { return map.width(); }
		auto height () const noexcept -> decltype(map.width()) { return map.height(); }
#endif

		chartype &operator() (int x, int y) { return map(x, y); }
		chartype operator() (int x, int y) const { return map(x, y); }

		chartype &operator[] (int n) { return map[n]; }
		chartype operator[] (int n) const { return map[n]; }

		enum direction {none = 0, N, E, S, W, NE, SE, SW, NW};

		bool in_range (direction d) const noexcept;
		chartype &in_direction (direction d);
		chartype in_direction (direction d) const;

		chartype &here () { return in_direction(none); }
		chartype here () const { return in_direction(none); }

		bool is_clear (direction d) const noexcept {
			return in_range(d) && in_direction(d) != '#';
		}

		direction move (direction d);

	};

} // namespace game

#endif // GAME_APP_H_
