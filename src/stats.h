#if defined(HAVE_CONFIG_H)
#include <config.h>
#elif defined(HAVE_CMAKECONFIG_H)
#include <cmakedefine.h>
#endif

#ifndef GAME_STATS_H_
#define GAME_STATS_H_

namespace game {
	class Stats {
	protected:
		int max_health_;
		int health_;
		int attack_;
		int defense_;
		int speed_;
	public:

#if defined(HAVE_AUTO_RETURN) || defined(HAVE_CXX14) || __cplusplus > 201400
#define GETTER(var) auto var () const noexcept { return var ## _ ; }
#else
#define GETTER(var) decltype(var ## _) var () const noexcept { return var ## _ ; }
#endif
		GETTER(max_health)
		GETTER(health)
		GETTER(attack)
		GETTER(defense)
		GETTER(speed)
#undef GETTER

		Stats (int h, int a, int d, int s): max_health_(h), health_(h), attack_(a), defense_(d), speed_(s) {}

		int hit (Stats &other) const noexcept {
			other.health_ -= attack_ - other.defense_ + 1;
			return attack_ - other.defense_ + 1;
		}

		int heal (int amt) noexcept {
			if (amt < 0) return 0;
			int oh = health_;
			health_ = health_ + amt < max_health_ ? health_ + amt : max_health_;
			return health_ - oh;
		}
	}; // class Stats
}

#endif // GAME_STATS_H_
