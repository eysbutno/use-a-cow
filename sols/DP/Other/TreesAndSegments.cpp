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
    int n, k; cin >> n >> k;
    vector<bool> s(n + 2);
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        s[i] = (c == '1');
    }
    auto calc = [&]() -> vector<vector<array<int, 2>>> {
        vector dp(n + 2, vector(k + 1, array<int, 2>{0, 0}));
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                for (int v = 0; v < 2; v++) {
                    int prv = j - (v != s[i]);
                    if (prv >= 0) {
                        dp[i][j][v] = 1 + dp[i - 1][prv][v];
                    }
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                smax(dp[i][j][0], dp[i - 1][j][0]);
                smax(dp[i][j][1], dp[i - 1][j][1]);
            }
            for (int j = 1; j <= k; j++) {
                smax(dp[i][j][0], dp[i][j - 1][0]);
                smax(dp[i][j][1], dp[i][j - 1][1]);
            }
        }
        return dp;
    };
    auto pf = calc();
    reverse(all(s));
    auto sf = calc();
    reverse(all(sf));
    vector<int> opt(n + 1, -1);
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            smax(opt[pf[i][j][0]], sf[i + 1][k - j][1]);
            smax(opt[sf[i + 1][k - j][0]], pf[i][j][1]);
        }
    }
    auto val = [&](int a) -> ll {
        ll best = 0;
        for (int i = 0; i <= n; i++) {
            if (opt[i] != -1) {
                smax(best, (ll) (a * i + opt[i]));
            }
        }
        return best;
    };
    for (int i = 1; i <= n; i++) {
        cout << val(i) << (i < n ? " " : "\n");
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: D. Trees and Segments.
 * Calculate which values of l_0 are reachable,
 * and if so, the maximum achievable value of l_1.
 * To do this, let dp[i][j][k] be the maximum subsegment
 * you can achieve with value k, if it's in the prefix
 * of i, and you use j operations in total. Then, use
 * prefix and suffix arrays.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/