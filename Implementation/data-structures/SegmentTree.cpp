#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename Info> class SegmentTree {
  private:
    const int len; 
    std::vector<Info> t; 
    
  public:
    SegmentTree(int len) : len(len), t(2 * len) {}
    SegmentTree(const std::vector<Info> &arr) 
        : len(arr.size()), t(2 * len) {
        for (int i = 0; i < len; i++) {
            t[i + len] = arr[i];
        }

        for (int i = len - 1; i > 0; i--) {
            t[i] = t[i << 1] + t[i << 1 | 1];
        }
    }

    void set(int idx, Info val) {
        for (t[idx += len] = val; idx >>= 1; ) {
            t[idx] = t[idx << 1] + t[idx << 1 | 1];
        }
    }

    /** @return query on [l, r) */
    Info qry(int l, int r) {
        Info res_l = Info(), res_r = Info();
        for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
            if (l & 1) { res_l = res_l + t[l++]; }
            if (r & 1) { res_r = t[--r] + res_r; }
        }
        return res_l + res_r;
    }
    
    /** @return value at location idx */
    Info get(int idx) {
        return t[idx + len];
    }
};

struct Info {

};

/** @return result of joining nodes a and b together */
Info operator+(const Info &a, const Info &b) {
    
}