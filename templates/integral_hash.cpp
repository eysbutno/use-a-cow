#include <bits/stdc++.h>

using ll = long long;

/**
 * This hash is for unordered maps.... probably wouldn't use it
 * most of the time TBH, but it could help for cheesing!
 * Would use like: unordered_map<int, T, integral_hash>
 */
struct integral_hash {
	const uint64_t C = uint64_t(2e18 * 3.1415927) + 71;
	const uint32_t R = std::chrono::steady_clock::now().time_since_epoch().count();
	size_t operator()(uint64_t x) const {
		return __builtin_bswap64((x ^ R) * C);
	}
};
