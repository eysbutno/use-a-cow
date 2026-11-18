#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000
int main() {
    int n, x; cin >> n >> x;
    vector<int> coins(n);
    vector<int> dp(x + 1);
    for (int &i : coins) cin >> i;
    for (int i = 1; i <= x; i++) {
        dp[i] = INF;
        for (int j : coins) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], dp[i - j] + 1);
            }
        }
    }
    int ans = dp[x];
    if (ans == INF) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}