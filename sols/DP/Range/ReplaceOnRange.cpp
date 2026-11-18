#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (int& i : a) cin >> i, --i;
    vector dp(n, vector(n, vector(x, n + 1)));
    vector dp2(n, vector(n, vector(x, n + 1)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < x; j++) {
            dp[i][i][j] = a[i] == j ? 0 : 1;
            dp2[i][i][j] = a[i] == j ? 1 : 0;
        }
    }
    for (int d = 1; d < n; d++) {
        for (int l = 0; l + d < n; l++) {
            int r = l + d;
            vector<pii> updates;
            for (int k = 0; k < x; k++) {
                for (int s = l; s < r; s++) {
                    smin(dp[l][r][k], dp[l][s][k] + dp[s + 1][r][k]);
                    smin(dp2[l][r][k], dp2[l][s][k] + dp2[s + 1][r][k]);
                }
                smin(dp[l][r][k], dp2[l][r][k] + 1);
                updates.push_back({dp[l][r][k], k});
            }
            sort(all(updates));
            for (int k = 0; k < x; k++) {
                for (auto [v, c] : updates) {
                    if (k != c) {
                        smin(dp2[l][r][k], v);
                        break;
                    }
                }
            }
        }
    }
    int mn = n + 1;
    for (int i = 0; i < x; i++) {
        smin(mn, dp[0][n - 1][i]);
    }
    cout << mn << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Replace on Segment.
 * Use Range DP to solve this problem.
 * Let dp[l][r][k] be the cost to turn
 * [l, r] into color k. Then, we have the
 * following state transition:
 * smin(dp[l][r][k], dp[l][i][k] + dp[i + 1][r][k]).
 * smin(dp[l][r][k], dp2[l][r][k] + 1).
 * dp2[l][r][k] = cost to make [l, r] anything that isn't k.
 * 
 * dp2 is calculated as follows:
 * smin(dp2[l][r][k], dp[l][r][m]), m != k.
 * smin(dp2[l][r][k], dp2[l][i][k] + dp2[i + 1][r][k]).
 * 
 * To solve the cyclic dependency issue, observe that
 * dp[l][r][k] never strictly requires dp2[l][r][k].
 * Why? Because, the previous ranges would have factored
 * in their dp[l][r][k] into its calculations.
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * See if there are some "restrictions" that you
  * can place, to limit it to a set of states. This
  * often makes life a million times easier!
  * Actually do something and don't just stare at
  * the screen....!
*/
/*
const int MOD = 1e9 + 7;
template<class T> void add(T& a, T b) {
	a += b, a %= MOD;
}
template<class T> void sub(T& a, T b) {
	a > b ? a -= b : a -= b, a += MOD;
}
template<class T> void mul(T& a, T b) {
	a = (a * b) % MOD;
}
*/