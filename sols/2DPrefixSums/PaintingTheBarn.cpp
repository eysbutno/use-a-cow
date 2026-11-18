#include <bits/stdc++.h>
using namespace std;

int dp[1001][1001];
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    //freopen("paintbarn.in", "r", stdin);
    //freopen("paintbarn.out", "w", stdout);
    int n, k; cin >> n >> k;
    while (n--) {
        int fx, fy, lx, ly;
        cin >> fx >> fy >> lx >> ly;
        dp[fx][fy]++, dp[lx][ly]++,
        dp[fx][ly]--, dp[lx][fy]--;
    }
    int ans = 0;
    for (int i = 0; i <= 1000; i++) {
        for (int j = 0; j <= 1000; j++) {
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
            if (i != 0 && j != 0) dp[i][j] -= dp[i - 1][j - 1];
            if (dp[i][j] == k) ans++;
        }
    }
    cout << ans << "\n";
    for (int i = 0; i <= 8; i++) {
        for (int j = 0; j <= 8; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }
}