#include <bits/stdc++.h>

using ll = long long;

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
 * makes it much easier. But I'm also way too lazy to write 3 prime NTT lol.
 */

int modpow(int x, ll n, int m) {
    ll res = 1, b = x % m;
    for (; n; n >>= 1, b = b * b % m) {
        if (n & 1) res = res * b % m;
    }

    return res;
}

template <int M, int G = 3> struct ntt {
    static void dft(std::vector<int> &a) {
        const int n = a.size();
        assert((n & (n - 1)) == 0);

        static std::vector<int> rt{1, 1};
        while (rt.size() < n) {
            int h = rt.size();
            rt.resize(2 * h);
            const int w = modpow(G, (M - 1) / (2 * h), M);  // primitive (2h)-th root
            rt[h] = 1;
            for (int k = 1; k < h; k++) rt[h + k] = 1ll * rt[h + k - 1] * w % M;
        }

        for (int i = 1, j = 0; i < n; i++) {
            int bit = n >> 1;
            for (; j & bit; bit >>= 1) j ^= bit;
            j ^= bit;
            if (i < j) std::swap(a[i], a[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
            const int h = len / 2;
            for (int i = 0; i < n; i += len) {
                for (int k = 0; k < h; k++) {
                    int u = a[i + k];
                    int v = 1ll * rt[h + k] * a[i + k + h] % M;
                    int s = u + v, d = u - v;
                    a[i + k] = (u + v) % M;
                    a[i + k + h] = (u -v + M) % M;
                }
            }
        }
    }

    static std::vector<int> conv(std::vector<int> a, std::vector<int> b) {
        // lol yosupo RTEs me if I don't have this
        if (a.size() == 1 && b.size() == 1) {
            return std::vector<int>{1ll * a[0] * b[0] % M};
        }

        // must be power of 2, for implementation convenience
        const int sz = 2 << std::__lg(a.size() + b.size() - 2);
        const int res_sz = a.size() + b.size() - 1;
        a.resize(sz);
        b.resize(sz);
        dft(a);
        dft(b);
        std::vector<int> c(sz);
        for (int i = 0; i < sz; i++) {
            c[i] = 1ll * a[i] * b[i] % M;
        }

        dft(c);
        std::reverse(c.begin() + 1, c.end());
        const int inv = modpow(sz, M - 2, M);
        for (int &i : c) i = 1ll * i * inv % M;

        c.resize(res_sz);
        return c;
    }
};

template<int M> std::vector<int> conv_mod(const std::vector<int>& a, const std::vector<int>& b) {
    const ll m1 = 998244353, m2 = 167772161, m3 = 469762049;
    auto r1 = ntt<m1, 3>::conv(a, b);
    auto r2 = ntt<m2, 3>::conv(a, b);
    auto r3 = ntt<m3, 3>::conv(a, b);

    ll inv_m1_m2 = modpow(m1, m2 - 2, m2);
    ll inv_m1m2_m3 = modpow(m1 % m3 * (m2 % m3) % m3, m3 - 2, m3);
    ll m1m2_mod = m1 * m2 % M;

    std::vector<int> res(r1.size());
    for (int i = 0; i < res.size(); i++) {
        ll x1 = r1[i];
        ll x2 = ((r2[i] - x1) % m2 + m2) % m2 * inv_m1_m2 % m2;
        ll t  = (x1 + x2 * m1) % m3;
        ll x3 = ((r3[i] - t) % m3 + m3) % m3 * inv_m1m2_m3 % m3;
        res[i] = (x1 + x2 * m1 % M + x3 * m1m2_mod) % M;
    }

    return res;
}

using ntt998 = ntt<998244353>; // example usage