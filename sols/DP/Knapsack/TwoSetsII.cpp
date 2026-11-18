#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
const int MAXN = 501;
const int MAXS = 2e5;
int dp[MAXN][MAXS];
int main() {
    int n; cin >> n;
    int sum = n * (n + 1) / 2;
    if (sum % 2) {
        cout << 0 << "\n";
        return 0;
    }
    sum /= 2; dp[0][0] = 1; // 1 way
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum; j++) {
            dp[i][j] += dp[i - 1][j];
            if (j - i >= 0) {
                dp[i][j] += dp[i - 1][j - i];
            }
            dp[i][j] %= MOD;
        }
    }
    cout << dp[n - 1][sum] << "\n";
}