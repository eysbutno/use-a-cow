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
    int n, m, k;
    cin >> n >> m >> k;
    vector<bool> bad(n + 1);
    for (int i = 0; i < k; i++) {
        int a; cin >> a;
        bad[a] = true;
    }
    int prv = 0;
    for (int i = 1; i <= n; i++) {
        if (bad[i]) continue;
        if (i - prv > m) {
            cout << -1 << "\n";
            return;
        } else {
            prv = i;
        }
    }
    using ld = long double;
    vector<array<ld, 2>> dp(n + 1, {0, 0});
    array<ld, 2> pf = {0, 0};
    for (int i = n - 1; i >= 0; i--) {
        if (i + m + 1 <= n) {
            pf = {pf[0] - dp[i + m + 1][0],
                  pf[1] - dp[i + m + 1][1]};
        }
        pf = {pf[0] + dp[i + 1][0], pf[1] + dp[i + 1][1]};
        if (bad[i]) {
            dp[i] = {0, 1};
        } else {
            const ld mult = 1.0 / m;
            dp[i][0] = {mult * pf[0] + 1};
            dp[i][1] = {mult * pf[1]};
        }
    }
    cout << fixed << setprecision(10);
    cout << (dp[0][0] / (1.0 - dp[0][1])) << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * f(x) = expected value of # of moves, starting from square i.
 * Then, f(x) is the following:
 * Z (if x is a bad square), or 1 + 1/m * (sum of f(x + d))
 * Note that because we set Z to be some arbitrary variable,
 * we can just track the coefficient.
*/