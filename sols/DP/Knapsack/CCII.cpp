#include <bits/stdc++.h>
using namespace std;
 
const int MOD = 1e9 + 7;
int main() {
    int n, x; cin >> n >> x;
    vector<int> coins(n);
    vector<int> dp(x + 1); dp[0] = 1;
    for (int &i : coins) cin >> i;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= x; j++) {
            if (j - coins[i] >= 0) {
                dp[j] += dp[j - coins[i]];
                dp[j] %= MOD;
            }
        }
    }
    cout << dp[x] << "\n";
}