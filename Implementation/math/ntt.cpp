#include <bits/stdc++.h>

using ll = long long;

constexpr int MOD = 998244353;

/**
 * TL;DR of NTT: literally just FFT,
 * but instead of complex numbers being our group,
 * we have integers mod M as it. 
 * 
 * Fact: for primitive root m in integers mod M, 
 * m | M - 1 (don't know proof yet, just trust)
 * 
 * And as a follow up, construction for 
 * x^m = 1 is y^((M-1) / m), where y is 
 * the primitive root of x (ie, it is a primitive root
 * for m=P or something like that!)
 * 
 * AC: https://judge.yosupo.jp/submission/416731
 * 
 * For 1e9 + 7, you need to use CRT. But I don't know CRT,
 * and I'm too lazy to learn it.
 * 
 * Note: I use mod as a template parameter, since for 1e9 + 7 this
 * makes it much easiser.
 */

int modpow(int x, ll n, int m) {
    ll res = 1, b = x % m;
    for (; n; n >>= 1, b = b * b % m) {
        if (n & 1) res = res * b % m;
    }
    return (int)res;
}

int modpow(int x, ll n, int m) {
    ll res = 1, b = x % m;
    for (; n; n >>= 1, b = b * b % m) {
        if (n & 1) res = res * b % m;
    }
    return (int)res;
}

template <int M, int G = 3> struct ntt {
    static void dft(std::vector<int> &a) {
        const int n = a.size();
        assert((n & (n - 1)) == 0);

        // 1. bit-reversal permutation (in place via swaps)
        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) std::swap(a[i], a[j]);
        }

        // 2. butterflies, bottom-up
        for (int len = 2; len <= n; len <<= 1) {
            const int w = modpow(3, (M - 1) / len, M);
            for (int i = 0; i < n; i += len) {
                int w_k = 1;
                for (int k = 0; k < len / 2; k++) {
                    int u = a[i + k];
                    int v = 1ll * w_k * a[i + k + len / 2] % MOD;
                    a[i + k] = (u + v) % MOD;
                    a[i + k + len / 2] = (u - v + MOD) % MOD;
                    w_k = 1ll * w_k * w % MOD;
                }
            }
        }
    }

    static std::vector<int> ntt(std::vector<int> a, std::vector<int> b) {
        // must be power of 2, for implementation convenience
        const int sz = 2 << std::__lg(a.size() + b.size() - 2);
        const int res_sz = a.size() + b.size() - 1;
        a.resize(sz);
        b.resize(sz);
        dft(a);
        dft(b);
        std::vector<int> c(sz);
        for (int i = 0; i < sz; i++) {
            c[i] = 1ll * a[i] * b[i] % MOD;
        }

        dft(c);
        std::reverse(c.begin() + 1, c.end());
        const int inv = modpow(sz, MOD - 2, MOD);
        for (int &i : c) i = 1ll * i * inv % MOD;

        c.resize(res_sz);
        return c;
    }
};

using ntt998 = ntt<998244353>;