#include <bits/stdc++.h>

using ll = long long;

/**
 * Binary search template.
 * NOTE: If there is no value in the range that
 * satisfies the function, it returns an endpoint.
 * Make sure to account for this.
 * 
 * (alternatively, use ranges::partition_point with views::iota)
*/
template <typename T, typename F> 
T first_true(T lo, T hi, const F &fn) {
    while (lo < hi) {
        T m = lo + (hi - lo) / 2;
        fn(m) ? hi = m : lo = m + 1;
    }
    return lo;
}

template <typename T, typename F> 
T last_true(T lo, T hi, const F &fn) {
    while (lo < hi) {
        T m = lo + (hi - lo + 1) / 2;
        fn(m) ? lo = m : hi = m - 1;
    }
    return lo;
}