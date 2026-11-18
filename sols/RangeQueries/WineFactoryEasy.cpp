#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
namespace SegmentTree {
    /**
     * Iterates over the given range, and applies
     * the function passed in.
    */
    template <typename F>
    auto forRange(int lf, int rt, F f) {
        for (; lf < rt; lf >>= 1, rt >>= 1) {
            if (lf & 1) f(lf++);
            if (rt & 1) f(--rt);
        }
    } 
    /**
     * Calculates the base 2 logarithm.
    */
    auto log2(int x) {
        return 31 - __builtin_clz(x);
    }
    /**
     * Iterates over the parents, and applies
     * the operation f on all the parents of p.
    */
    template <typename F>
    auto forParents(int p, bool dir, F f) {
        const auto lvls = log2(p);
        for (auto i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
}
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<int> a(n), b(n);
    for (int &i : a) cin >> i;
    for (int &i : b) cin >> i;
    for (int i = 1; i < n; i++) {
        ll c; cin >> c;
    }
    vector<ll> t(n << 1), lz(n);
    for (int i = n - 1; i >= 0; i--) {
        t[i + n] = a[i] - b[i];
        if (i + 1 < n) t[i + n] += t[i + n + 1];
    }
    const auto pull = [&](int node) {
        t[node] = max(t[node << 1], t[node << 1 | 1]) + lz[node];
    };
    for (int i = n - 1; i >= 1; i--) {
        pull(i);
    }
    ll sum = accumulate(all(a), 0LL);
    while (q--) {
        int p, x, y; ll z;
        cin >> p >> x >> y >> z;
        sum += x - a[--p];
        const int dx = (x - y) - (a[p] - b[p]);
        SegmentTree::forRange(n, n + p + 1, [&](int idx) {
            if (idx < n) lz[idx] += dx;
            t[idx] += dx;
        });
        SegmentTree::forParents(n, true, pull);
        SegmentTree::forParents(n + p, true, pull);
        cout << sum - max(0LL, t[1]) << "\n";
        a[p] = x, b[p] = y;
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * F1. Wine Factory (Easy Version)
 * Obviously, because 10^18 > 10^9, we can just
 * flat out ignore the pipe's capacity... lol.
 * 
 * So, the answer is just the sum of a_i, minus
 * all the leftover water. The leftover water, in essence,
 * is the max suffix sum of a_i - b_i.
*/