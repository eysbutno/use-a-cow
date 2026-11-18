#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)

const int MOD = 1e9 + 7;
ll dp[101][1001];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> h(n);
    int mn = 2e9, mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        smin(mn, h[i]);
        smax(mx, h[i]);
    }
    auto res = [&](int fin) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= mx; j++) {
                dp[i][j] = 0;
            }
        }
        for (int i = fin; i <= h[0]; i++) {
            dp[0][i] = 1;
        }
        for (int i = 1; i < n; i++) {
            for (int j = fin; j <= h[i]; j++) {
                if (h[i - 1] >= j) {
                    dp[i][j] = dp[i - 1][h[i - 1] - (j - fin)];
                    dp[i][j] %= MOD;
                }
                if (j > fin) dp[i][j] += dp[i][j - 1];
                dp[i][j] %= MOD;
            }
        }
        return dp[n - 1][h[n - 1]];
    };
    ll ans = 0;
    if (n % 2 == 0) mn = 0;
    for (int i = 0; i <= mn; i++) {
        ans = (ans + res(i)) % MOD;
    }
    cout << ans << '\n';
}
/**
 * TASK: Drought.
 * Break up this problem into
 * two cases.
 * 
 * Case 1: N is odd.
 * In this case, we have to brute force
 * every possible ending hunger value.
 * 
 * Case 2: N is even.
 * Given any number x that a tuple can
 * be reduced to, that tuple can also
 * be reduced to 0. Therefore, we only
 * DP with the condition that the hunger
 * value is eventually 0.
 * 
 * To DP this problem, (given the final hunger value),
 * we can essentially reduce this problem to counting
 * how many ways we can add numbers to adjacent cows,
 * so that it obeys the upper bounds of h.
*/