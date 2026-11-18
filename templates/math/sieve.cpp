#include <bits/stdc++.h>

using ll = long long;

/**
 * Stolen from jiangly. Made some edits.
 */
namespace sieve {
	std::vector<int> minp, primes;
	void init(int n) {
		minp.resize(n + 1);
		for (int i = 2; i <= n; i++) {
			if (minp[i] == 0) primes.push_back(minp[i] = i);

			for (int p : primes) {
				if (1ll * i * p > n) break;
				minp[i * p] = p;
				if (p == minp[i]) break;
			}
		}
	}

	bool is_prime(int x) {
		return minp[x] == x;
	}

	std::vector<std::array<int, 2>> factorize(int x) {
		std::vector<std::array<int, 2>> res;
		while (x > 1) {
			int v = minp[x];
			res.push_back({v, 0});
			while (x % v == 0) res.back()[1]++, x /= v;
		}

		return res;
	}
}