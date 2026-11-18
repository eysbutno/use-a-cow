#include <bits/stdc++.h>
using namespace std;
#define INF 2e9

int main() {
    int n; cin >> n;
    vector<int> h(n);
    for (int &i : h) cin >> i;
    vector<int> dp(n);
    for (int i = 1; i < n; i++) {
        dp[i] = INF;
        for (int j = 1; j <= 2; j++) {
            if (i - j >= 0) {
                dp[i] = min(dp[i], abs(h[i - j] - h[i]) + dp[i - j]);
            }
        }
    }
    cout << dp[n - 1] << "\n";
}