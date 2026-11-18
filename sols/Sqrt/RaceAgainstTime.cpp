#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

#ifdef LOCAL
#include "../src/debug.hpp"
#else
#define debug(...) 420
#endif
// g++ -DLOCAL -Wall Practice.cpp -o bin

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n, q;
    cin >> n >> q;
    const int b = sqrt(n * __lg(n));
    vector<vector<int>> it;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int idx = i / b;
        if (sz(it) == idx) it.push_back({});
        int x; cin >> x;
        it[idx].push_back(a[i] = x);
    }
    for (auto &i : it) {
        sort(all(i));
    }
    const auto upd = [&]() -> void {
        int i, x;
        cin >> i >> x;
        int idx = (--i) / b;
        int loc = lower_bound(all(it[idx]), a[i]) - begin(it[idx]);
        it[idx][loc] = a[i] = x;
        sort(all(it[idx]));
    };
    const auto qry = [&]() -> void {
        int p, q, x;
        cin >> p >> q >> x;
        --p, --q;
        int lf = p / b, rt = q / b;
        int res = 0;
        if (lf == rt) {
            for (int i = p; i <= q; i++) {
                res += (a[i] <= x);
            }
        } else {
            for (int y : {lf, rt}) {
                for (int i = b * y; i <= min(b * (y + 1) - 1, n - 1); i++) {
                    if (p <= i && i <= q) res += (a[i] <= x);
                }
            }
            for (int y = lf + 1; y < rt; y++) {
                res += upper_bound(all(it[y]), x) - begin(it[y]);
            }
        }
        cout << res << "\n";
    };
    while (q--) {
        char c; cin >> c;
        c == 'C' ? qry() : upd();
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Divide the array into blocks of 
 * size B = sqrt(N log N). Keep sorted
 * arrays within each block for queries.
*/