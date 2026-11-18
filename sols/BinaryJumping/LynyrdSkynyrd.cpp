#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> p(n), mp(n), a(m);
    for (int i = 0; i < n; i++) {
        cin >> p[i], --p[i];
        mp[p[i]] = i;
    }
    for (int &i : a) {
        cin >> i, --i;
    }
    vector<int> lst(n, m);
    const int LOG = 32 - __builtin_clz(n);
    vector lift(LOG, vector(m + 1, m));
    for (int i = m - 1; i >= 0; i--) {
        int nxt = p[(mp[a[i]] + 1) % n];
        lift[0][i] = lst[nxt], lst[a[i]] = i;
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 0; j < m; j++) {
            lift[i][j] = lift[i - 1][lift[i - 1][j]];
        }
    }
    vector<int> res(m);
    for (int i = m - 1; i >= 0; i--) {
        int dx = n - 1, idx = i;
        for (int j = LOG - 1; j >= 0; j--) {
            if (dx >> j & 1) idx = lift[j][idx];
        }
        res[i] = idx;
        if (i + 1 < m) {
            smin(res[i], res[i + 1]);
        }
    }
    while (q--) {
        int l, r; cin >> l >> r;
        cout << (res[--l] < r);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Precalculate an array b, such that 
 * b[i] points to the next index that is
 * needed in our cyclic permutation. Then,
 * for every starting point, binary lift on
 * it. Afterwards, either use RMQ or just
 * compute prefix/suffix maxima.
*/