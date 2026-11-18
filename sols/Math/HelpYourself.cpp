#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    // freopen("help.in", "r", stdin);
    // freopen("help.out", "w", stdout);
    int n; cin >> n;
    vector<int> p(n * 2 + 1);
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        p[x]++, p[y]--;
    }
    vector<ll> pw(n + 1);
    pw[0] = 1;
    for (int i = 1; i <= n; i++) {
        pw[i] = (2LL * pw[i - 1]) % MOD;
    }
    ll tot = 0;
    int open = 0;
    for (int i = 0; i <= n * 2; i++) {
        open += p[i];
        if (p[i] == 1) {
            tot += pw[n - open];
            tot %= MOD;
        }
    }
    cout << tot << '\n';
}
/**
 * 1. Bounds on l_i, r_i are low.
 * 2. All points are distinct.
 * 
 * We only add the # of intervals a component
 * exists for when we add the "open" interval.
 * This is to prevent overcounting.
*/