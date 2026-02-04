#include <bits/stdc++.h>

using ll = long long;

template<typename T> struct FT {
    const int n; 
    std::vector<T> t;
    FT(int _n) : n(_n + 1), t(n) {}

    T pre(int i) {
        T s = 0;
        for (i++; i > 0; i -= i & -i) s += t[i];
        return s;
    }

    void upd(int i, T x) {
        for (i++; i < n; i += i & -i) t[i] += x;
    }

    T qry(int l, int r) { return pre(r) - pre(l - 1); }
};