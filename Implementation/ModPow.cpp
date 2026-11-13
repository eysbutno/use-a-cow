#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/** @return x^n % m */
int modpow(int x, ll n, int m) {
    ll res = 1, b = x % m;
    for (; n; n >>= 1, b = b * b % m) {
        if (n & 1) res = res * b % m;
    }
    return (int)res;
}