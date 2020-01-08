#include "app.h"

namespace game {
	bool Application::in_range (Application::direction d) const noexcept {
		switch (d) {
		case none:
			return map.in_range(x, y - 1);
		case N:
			return map.in_range(x, y - 1);
		case E:
			return map.in_range(x + 1, y);
		case S:
			return map.in_range(x, y + 1);
		case W:
			return map.in_range(x - 1, y);
		case NE:
			return map.in_range(x + 1, y - 1);
		case SE:
			return map.in_range(x + 1, y + 1);
		case SW:
			return map.in_range(x - 1, y + 1);
		case NW:
			return map.in_range(x - 1, y - 1);
		}
		return false;
	}

	// Performs no error checking
	char &Application::in_direction (Application::direction d) {
		switch (d) {
		case none:
			return map(x, y);
		case N:
			return map(x, y - 1);
		case E:
			return map(x + 1, y);
		case S:
			return map(x, y + 1);
		case W:
			return map(x - 1, y);
		case NE:
			return map(x + 1, y - 1);
		case SE:
			return map(x + 1, y + 1);
		case SW:
			return map(x - 1, y + 1);
		case NW:
			return map(x - 1, y - 1);
		}
		return map(x, y);
	}

	// Performs no error checking
	char Application::in_direction (Application::direction d) const {
		switch (d) {
		case none:
			return map(x, y);
		case N:
			return map(x, y - 1);
		case E:
			return map(x + 1, y);
		case S:
			return map(x, y + 1);
		case W:
			return map(x - 1, y);
		case NE:
			return map(x + 1, y - 1);
		case SE:
			return map(x + 1, y + 1);
		case SW:
			return map(x - 1, y + 1);
		case NW:
			return map(x - 1, y - 1);
		}
		return map(x, y);
	}

	Application::direction Application::move (Application::direction d) {
		if (d <= W && !is_clear(d)) return none;
		switch (d) {
		case none:
			return none;
		case N:
			y--;
			return N;
		case S:
			y++;
			return S;
		case E:
			x++;
			return E;
		case W:
			x--;
			return W;
		case NE:
			if (is_clear(d)) {
				--y; ++x;
				return NE;
			} else if (is_clear(E)) {
				++x;
				return E;
			} else if (is_clear(N)) {
				y--;
				return N;
			}
			break;
		case SE:
			if (is_clear(d)) {
				++x; ++y; return SE;
			} else if (is_clear(E)) {
				++x; return E;
			} else if (is_clear(S)) {
				++y; return S;
			}
		case SW:
			if (is_clear(d)) {
				--x; ++y; return SW;
			} else if (is_clear(W)) {
				--x; return W;
			} else if (is_clear(S)) {
				++y; return N;
			}
			break;
		case NW:
			if (is_clear(d)) {
				--x; --y; return NW;
			} else if (is_clear(W)) {
				--x; return W;
			} else if (is_clear(N)) {
				--y; return N;
			}
			break;
		}
		return none;
	}
} // namespace game
