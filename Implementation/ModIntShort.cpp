#include <bits/stdc++.h>

using ll = long long;

template<int MOD> struct mint {
    int v; 
    constexpr mint() : v(0) {}
    constexpr mint(long long _v) : v (int(_v % MOD)) { v += (v < 0) * MOD; }
    explicit operator int() const { return v; } 
    mint& operator+=(mint o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    mint& operator-=(mint o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    mint& operator*=(mint o) { v = int(1ll * v * o.v % MOD); return *this; }
    mint& operator/=(mint o) { *this *= inv(o); return *this; }
    friend mint modpow(mint a, ll p) { return p ? modpow(a * a, p / 2) * (p & 1 ? a : 1) : 1; }
    friend mint inv(mint o) { return modpow(o, MOD - 2); }
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
};