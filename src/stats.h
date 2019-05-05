#ifndef GAME_STATS_H_
#define GAME_STATS_H_

namespace game {
	class Stats {
		int max_health_;
		int health_;
		int attack_;
		int defense_;
		int speed_;
	public:

		auto max_health () const noexcept { return max_health_; }
		auto health () const noexcept { return health_; }
		auto attack () const noexcept { return attack_; }
		auto defense () const noexcept { return defense_; }
		auto speed () const noexcept { return speed_; }

		Stats (int h, int a, int d, int s): max_health_(h), health_(h), attack_(a), defense_(d), speed_(s) {}

		int attack (Stats &other) const noexcept {
			other.health_ -= attack_ - other.defense_ + 1;
			return attack_ - other.defense_ + 1;
		}

		int heal (int amt) noexcept {
			if (amt < 0) return 0;
			int oh = health_;
			health_ = health_ + amt < max_health_ ? health_ + amt : max_health_;
			return health_ - oh;
		}
	};
}

#endif // GAME_STATS_H_
