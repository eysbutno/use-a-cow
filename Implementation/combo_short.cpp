#include <bits/stdc++.h>

using ll = long long;

constexpr int MOD = 998244353;

ll modpow(ll x, ll n, ll m = MOD) {
    ll res = 1;
    for (x %= m; n; n >>= 1, (x *= x) %= m) {
        if (n & 1) (res *= x) %= m;
    }
    return res;
}

namespace combo {
    std::vector<ll> fact, inv;

    void init(int n) {
        fact.resize(n + 1);
        inv.resize(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }
        inv[n] = modpow(fact[n], MOD - 2);
        for (int i = n; i >= 1; i--) {
            inv[i - 1] = (inv[i] * i) % MOD;
        }
    }

    ll nck(int n, int k) {
        if (k > n || k < 0) { return 0ll; }
        return fact[n] * inv[k] % MOD * inv[n - k] % MOD;
    }

    ll perm(int n, int k) {
        if (k > n || k < 0) { return 0ll; }
        return fact[n] * inv[n - k] % MOD;
    }
}