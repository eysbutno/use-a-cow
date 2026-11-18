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
    int n; cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    const int LOG = 30;
    vector pf(2, vector(LOG, vector(n + 2, 0)));
    vector sf(2, vector(LOG, vector(n + 2, 0)));
    for (int i = 0; i < LOG; i++) {
        for (int j = 1; j <= n; j++) {
            int p = (a[j] >> i) & 1;
            for (int k = 0; k < 2; k++) {
                pf[k][i][j] = (p == k) + pf[k ^ p][i][j - 1];
            }
        }
        for (int j = n; j >= 1; j--) {
            int p = (a[j] >> i) & 1;
            for (int k = 0; k < 2; k++) {
                sf[k][i][j] = (p == k) + sf[k ^ p][i][j + 1];
            }
        }
    }
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        int msb = 31 - __builtin_clz(a[i]);
        res += 1ll * pf[1][msb][i - 1] * (1 + sf[0][msb][i + 1]);
        res += 1ll * (1 + pf[0][msb][i - 1]) * sf[1][msb][i + 1];
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * f(x, y - 1) xor f(y + 1, z) > f(x, z).
 * Consider a[y] and its MSB i. Let xor
 * f(x, y - 1) xor f(y + 1, z) be r. If, at i,
 * r has its value be 1, then obviously stuff
 * does not work out. Thus, r has to have its value
 * at said MSB be 0. As long as r, at i, is 0, then
 * all the subarrays work out.
*/