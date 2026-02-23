#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename info> class segtree {
  private:
    const int len; 
    std::vector<info> t; 
    
  public:
    segtree(int len) : len(len), t(2 * len) {}
    segtree(const std::vector<info> &arr) 
        : len(arr.size()), t(2 * len) {
        for (int i = 0; i < len; i++) {
            t[i + len] = arr[i];
        }

        for (int i = len - 1; i > 0; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void set(int idx, info val) {
        for (t[idx += len] = val; idx >>= 1; ) {
            t[idx] = t[idx << 1] + t[idx << 1 | 1];
        }
    }

    /** @return query on [l, r) */
    info qry(int l, int r) {
        info res_l = info(), res_r = info();
        for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { res_l = res_l + t[l++]; }
            if (r & 1) { res_r = t[--r] + res_r; }
        }
        return res_l + res_r;
    }
    
    /** @return value at location idx */
    info get(int idx) {
        return t[idx + len];
    }
};

struct info {

};

/** @return result of joining nodes a and b together */
info operator+(const info &a, const info &b) {
    
}