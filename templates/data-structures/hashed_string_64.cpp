#include <bits/stdc++.h>

using ll = long long;

/**
 * Faster, more lightweight string hashing
 * template. Taken from USACO Guide, with some edits.
 */
class hashed_string {
  private:
	static const ll M = 1e9 + 9;
	static const ll B;
	static std::vector<ll> pow;
	std::vector<ll> p_hash;

  public:
	hashed_string() {}
	hashed_string(const std::string &s) : p_hash(s.size() + 1) {
		while (pow.size() <= s.size()) { 
            pow.push_back((pow.back() * B) % M); 
        }

		p_hash[0] = 0;
		for (int i = 0; i < s.size(); i++) {
			p_hash[i + 1] = ((p_hash[i] * B) % M + s[i]) % M;
		}
	}

    /** @return hash of [l, r] */
	long long get_hash(int l, int r) {
		ll raw = p_hash[r + 1] - (p_hash[l] * pow[r - l + 1]);
		return (raw % M + M) % M;
	}
};

std::vector<ll> hashed_string::pow = {1};
std::mt19937 rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count());
const ll hashed_string::B = std::uniform_int_distribution<ll>(0, M - 1)(rng);