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
template<class T> class FenwickTree {
    private:
        int sz; vector<T> arr;
    public:
        FenwickTree(int n) {
            sz = n + 1, arr.resize(n + 1);
        }
        FenwickTree() {}
        T prefix(int idx) { // [0, idx] sum
            T tot = 0;
            for (++idx; idx >= 1; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        T query(int l, int r) { // [l, r] sum
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < sz; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
FenwickTree<int> ft;
// global variable, so the lambdas work... lol
template<class T, class F> T firstTrue(T lo, T hi, F f) {
    ++hi; // returns hi + 1, if no result.
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        f(mid) ? hi = mid : lo = mid + 1;
    }
    return lo;
}
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    sort(all(a));
    ft = FenwickTree<int>(n + 1);
    auto add = [&](int l, int r, int v) -> void {
        // adds v to [l, r], so BIT will correctly query.
        ft.update(l, v), ft.update(r + 1, -v);
    };
    for (int i = 0; i < n; i++) {
        add(i, i, a[i]);
    }
    auto update = [&]() -> void {
        int c, h; cin >> c >> h;
        int l = firstTrue(0, n - 1, [&](int x) {
            return ft.prefix(x) >= h;
        }); 
        if (l == n) return;
        int r = l + c - 1;
        if (r >= n - 1) {
            add(l, r - 1, 1);
            return;
        }
        int edp = firstTrue(0, n - 1, [&](int x) {
            return ft.prefix(x) > ft.prefix(r);
        }); 
        if (r == edp - 1) {
            add(l, edp - 1, 1);
        } else {
            int split = firstTrue(0, n - 1, [&](int x) {
                return ft.prefix(x) >= ft.prefix(r);
            });
            add(l, split - 1, 1);
            int del = c - (split - l);
            add(edp - del, edp - 1, 1);
        }
    };
    auto query = [&]() -> void {
        int mn, mx; cin >> mn >> mx;
        int l = firstTrue(0, n - 1, [&](int x) {
            return ft.prefix(x) >= mn;
        });
        int r = firstTrue(0, n - 1, [&](int x) {
            return ft.prefix(x) > mx;
        });
        cout << r - l << "\n";
    };
    while (q--) {
        char c; cin >> c;
        (c == 'F') ? update() : query();
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * 2011 - Growing Trees (Baltic OI)
 * Use a binary indexed tree to handle range updates
 * to the tree heights. Pay extra attention to the following case:
 * a[r] == a[r + 1], where r is the last tree updated.
 * 
 * In this case, you can't range add like normal; instead, you have to
 * split up the range, for the array to be in sorted order.
*/