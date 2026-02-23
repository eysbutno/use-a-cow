#include <bits/stdc++.h>

using ll = long long;

/**
 * String hashing... stores the hashes for every prefix.
 * Build: O(n), Query: O(1).
 * Failure Probability: O(|S||H|^2 / M)
 * 
 * Note: If this is too slow, switch to the usaco.guide version
 * that doesn't use int128 but still uses randomized bases.
 */
struct hashed_string {
	static const ll M = (1ll << 61) - 1;
	static const ll B;
	static __int128 mul(ll a, ll b) { return (__int128) a * b; }
	static ll mod_mul(ll a, ll b) { return mul(a, b) % M; }

	static std::vector<ll> pow; // pow[i] = P^i % M
	std::vector<ll> p_hash;     // p_hash[i] = hash of first i characters in string

    hashed_string() {}
	hashed_string(const std::string &s) : p_hash(s.size() + 1) {
		while (pow.size() < s.size()) { pow.push_back(mod_mul(pow.back(), B)); }
		p_hash[0] = 0;
		for (int i = 0; i < (int) s.size(); i++) {
			p_hash[i + 1] = (mul(p_hash[i], B) + s[i]) % M;
		}
	}

	/** @return length of the string */
	inline int size() { return (int) p_hash.size() - 1; }

	/** @return hash of the substring [l, r] */
	ll get_hash(int l, int r) {
		ll res = p_hash[r + 1] - mod_mul(p_hash[l], pow[r - l + 1]);
		return (res + M) % M;
	}

	/** @return len of LCP, starting from st_1 and st_2 for each str */
    int lcp(hashed_string &other, int st_1 = 0, int st_2 = 0) {
        int lo = -1, hi = std::min(size() - st_1, other.size() - st_2);
        while (lo < hi) {
            int mi = (lo + hi + 1) / 2;
            ll pf_1 = get_hash(st_1, st_1 + mi);
            ll pf_2 = other.get_hash(st_2, st_2 + mi);
            (pf_1 == pf_2) ? lo = mi : hi = mi - 1;
        }
        return lo + 1;
    }
};

std::vector<ll> hashed_string::pow = {1};
std::mt19937 rng((uint32_t)std::chrono::steady_clock::now().time_since_epoch().count());
const ll hashed_string::B = std::uniform_int_distribution<ll>(0, M - 1)(rng);