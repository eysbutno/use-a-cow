#include <bits/stdc++.h>

using ll = long long;

/**
 * Hilbert Ordering for Mo's algorithm. Supposedly
 * provides better sorting orders for less pointer moves.
 */
ll hilbert_order(int x, int y) {
    const int logn = std::__lg(std::max(x, y) * 2 + 1) | 1;
    const ll maxn = (1ll << logn) - 1;
    ll res = 0;
    for (ll s = 1ll << (logn - 1); s; s >>= 1) {
        bool rx = x & s, ry = y & s;
        res = (res << 2) | (rx ? ry ? 2 : 1 : ry ? 3 : 0);
        if (!rx) {
            if (ry) x ^= maxn, y ^= maxn;
            std::swap(x, y);
        }
    }
    return res;
}