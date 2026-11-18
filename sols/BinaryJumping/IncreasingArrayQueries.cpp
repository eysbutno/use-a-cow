#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<ll> x(n), pf(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        pf[i] = x[i] + (i ? pf[i - 1] : 0);
    }
    const int LOG = 18;
    vector nxt(LOG, vector(n + 1, 0));
    vector data(LOG, vector(n + 1, 0LL));
    stack<int> active;
    for (int i = n - 1; i >= 0; i--) {
        while (sz(active) && x[active.top()] <= x[i]) {
            active.pop();
        }
        nxt[0][i] = sz(active) ? active.top() : n;
        data[0][i] = (nxt[0][i] - i) * x[i];
        active.push(i);
    }
    for (int i = 0; i < LOG; i++) {
        nxt[i][n] = n; // so binlift works
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 0; j < n; j++) {
            int split = nxt[i - 1][j];
            nxt[i][j] = nxt[i - 1][split];
            data[i][j] = data[i - 1][j] + data[i - 1][split];
        }
    }
    auto query = [&](int l, int r) -> ll {
        ll res = (l ? pf[l - 1] : 0) - pf[r];
        for (int i = LOG - 1; i >= 0; i--) {
            if (nxt[i][l] <= r) {
                res += data[i][l];
                l = nxt[i][l];
            }
        }
        res += (r - l + 1) * x[l];
        return res;
    };
    while (q--) {
        int l, r; cin >> l >> r;
        cout << query(--l, --r) << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Increasing Array Queries (CSES)
 * For each [l, r] query, consider the suffix. We only
 * care about the prefix maximums on the subarray [l, n], so we can
 * binary lift on the last prefix maximum that is <= r. Note that
 * we can also binary lift on the "sum" while finding the last
 * prefix maximum. 
 * 
 * Binary lifting on the sum works for the following reason. Here
 * is the "merging" for the binary lifting on the sum:
 * data[i][j] = data[i - 1][j] + data[i - 1][nxt[i - 1][j]]
 * 
 * nxt[i - 1][j] will be greater than the elements on [i, nxt[i - 1][j]),
 * so the combining works for obvious reasons.
*/