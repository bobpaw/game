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

#ifdef HAVE_CXX14
		auto
#else
		decltype(max_health_)
#endif
		max_health () const noexcept { return max_health_; }
#ifdef HAVE_CXX14
		auto
#else
		decltype(health_)
#endif
		health () const noexcept { return health_; }
#ifdef HAVE_CXX14
		auto
#else
		decltype(attack_)
#endif
		attack () const noexcept { return attack_; }
#ifdef HAVE_CXX14
		auto
#else
		decltype(defense_)
#endif
		defense () const noexcept { return defense_; }
#ifdef HAVE_CXX14
		auto
#else
		decltype(speed_)
#endif
		speed () const noexcept { return speed_; }

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
