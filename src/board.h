#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <functional> // std::function
#include <random> // std::random_device, std::default_random_engine, etc.
#include <stdexcept> // std::runtime_error, std::out_of_range
#include <type_traits>

#ifndef GAME_BOARD_H_
#define GAME_BOARD_H_

namespace game {
	class board {
	public:
		using chartype = char;

	private:
		int w;
		int h;
		chartype *map;

	public:
		// Constructors, Destructors, Copy/Move
		board (int width, int height, std::function<chartype(board*, int, int, int)> setter): w(width), h(height) {
			map = new chartype[height * width + 1]();
			if (map == nullptr) throw std::runtime_error("board::board() Out of memory");
			if (setter) {
				auto engine = std::default_random_engine(std::random_device()());
				auto distribution = std::uniform_int_distribution<int>(0);
				for (int y = 0; y < height; ++y)
					for (int x = 0; x < width; ++x)
						operator()(x, y) = setter(this, x, y, distribution(engine));
			}
		}

		board (int width, int height): board(width, height, nullptr) {}

		board (const board &old): w(old.w), h(old.h) {
			map = new chartype[old.h * old.w + 1]();
			if (map == nullptr) throw std::runtime_error("board::board() Out of memory");
			for (int i = 0; i < old.h * old.w; ++i) map[i] = old.map[i];
		}
		board& operator= (const board &old) {
			w = old.w;
			h = old.h;
			map = new chartype[h * w + 1]();
			if (map == nullptr) throw std::runtime_error("board copy assignment: Out of memory");
			for (int i = 0; i < h * w; ++i) map[i] = old.map[i];
			return *this;
		}

		board (board &&old): w(old.w), h(old.h), map(old.map) {}
		board &operator= (board &&old) {
			h = old.h;
			w = old.w;
			map = old.map;
			return *this;
		}

		~board () { delete[] map; }

		// Access
#ifdef HAVE_CXX14
		auto width () const noexcept { return w; }
		auto height () const noexcept { return h; }
#else
		decltype(w) width () const noexcept { return w; }
		decltype(h) height () const noexcept { return h; }
#endif

		chartype operator[] (int n) const { return map[n]; }
		chartype &operator[] (int n) { return map[n]; }

		chartype operator() (int x, int y) const {
			if (in_range(x, y)) return map[w * y + x];
			else throw std::out_of_range("base_map::operator() out of range");
		}
		chartype &operator() (int x, int y) {
			if (in_range(x, y)) return map[w * y + x];
			else throw std::out_of_range("base_map::operator() out of range");
		}

		bool in_range (int x, int y) const noexcept {
			return x < w && x >= 0 && y < h && y >= 0;
		}
	};

} // namespace game

#endif // GAME_GAME_MAP_H_
