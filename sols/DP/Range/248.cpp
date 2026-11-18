#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 250;
int dp[N][N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int n; cin >> n;
    vector<int> s(n);
    for (int& i : s) {
        cin >> i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    int res = *max_element(all(s));
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            if (l == r) {
                dp[l][r] = s[l];
                continue;
            }
            /**
             * Assume prefixes and
             * suffixes are already
             * calculated.
            */
            for (int div = l; div < r; div++) {
                if (dp[l][div] != -1 && dp[div + 1][r] != -1
                    && dp[l][div] == dp[div + 1][r]) {
                    smax(dp[l][r], dp[l][div] + 1);
                }
            }
            smax(res, dp[l][r]);
        }
    }
    cout << res << '\n';
}
/**
 * TASK: 248.
 * Idea: Use range DP. For
 * each subarray, calculate the max
 * value  you can reduce it to.
 * 
 * Run DP by doing each "subarray" in
 * terms of length, and then merging.
*/