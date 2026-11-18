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
const int MOD = 998244353;
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    sort(all(a));
    const int MX = 5001;
    vector<int> dp(MX);
    dp[0] = 1, dp[a[0]] = 1;
    ll res = a[0];
    for (int i = 1; i < n; i++) {
        vector<int> ndp(MX);
        for (int j = 0; j < MX; j++) {
            if (dp[j] == 0) continue;
            int v = (a[i] > j) ? a[i] : (j + a[i] + 1) / 2;
            res = (res + 1LL * v * dp[j]) % MOD;
            for (int k = 0; k < 2; k++) {
                ndp[j + k * a[i]] += dp[j];
                ndp[j + k * a[i]] %= MOD;
            }
        }
        dp = ndp;
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Colored Ball (CF)
 * For a group of balls, the value is the following:
 * 1. If no color's count > sum of the rest, it's just (sum + 1) / 2.
 * 2. Otherwise, it's the maximmum value of the balls.
 * This condition can be rewritten as:
 * Value = 2 * mx > sum ? mx : (sum + 1) / 2.
 * Then, we let our DP state be the sum of all the balls.
*/