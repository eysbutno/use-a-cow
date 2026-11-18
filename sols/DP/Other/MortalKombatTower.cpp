#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using pdi = pair<double, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    vector<int> dif(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> dif[i];
    }
    vector<vector<int>> dp(
        2, vector<int>(n + 1));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = 2e9;
        }
    }
    dp[0][0] = dif[0]; 
    dp[0][1] = dif[0] + dif[1];
    for (int i = 1; i < n; i++) {
        // switching states now
        dp[1][i] = min(dp[1][i], dp[0][i - 1]);
        dp[1][i + 1] = min(dp[1][i + 1], dp[0][i - 1]);
        dp[0][i] = min(dp[0][i], dp[1][i - 1] + dif[i]);
        dp[0][i + 1] = min(dp[0][i + 1], dp[1][i - 1]
            + dif[i] + dif[i + 1]);
    }
    cout << min(dp[0][n - 1], 
        dp[1][n - 1]) << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}
/*
Just DP it.
*/