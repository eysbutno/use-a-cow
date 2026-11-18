#include <bits/stdc++.h>

using ll = long long;

/**
 * <O(n log n), O(1)> RMQ implementation. Some stuff is
 * borrowed from tourist.
*/
template <class T> struct rmq {
    int n; 
    std::vector<std::vector<T>> st;
    
    void init(const std::vector<T> &a) {
        n = a.size();
        int max_log = 1 + std::__lg(n);
        st.resize(max_log);
        st[0] = a;
        for (int j = 1; j < max_log; j++) {
            st[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++) {
                st[j][i] = min(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    /** @return query on range [l, r] */
    T qry(int l, int r) const {
        int lg = std::__lg(r - l + 1);
        return std::min(st[lg][l], st[lg][r - (1 << lg) + 1]);
    }
};