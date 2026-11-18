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
    const int b = sqrt(n);
    vector<int> dp(n, 1);
    vector lz(b, vector(b, 0));
    for (int i = n - 1; i >= 0; i--) {
        if (a[i] >= b) {
            for (int j = i + a[i]; j < n; j += a[i]) {
                dp[i] = (dp[i] + dp[j]) % MOD;
            }
        } else {
            dp[i] = (dp[i] + lz[a[i]][i % a[i]]) % MOD;
        }
        for (int j = 1; j < b; j++) {
            lz[j][i % j] = (lz[j][i % j] + dp[i]) % MOD;
        }
    }
    cout << dp[0] << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Hop Sugoroku (AtCoder)
 * Trivial O(N^2) DP is just push DP bashing it.
 * For values of a_i > sqrt(n), we can just do the standard
 * push DP. Otherwise, we use the precalculated value for this
 * block size and this index (modulo block size), and add to it.
*/