#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    int t, a, b; cin >> t >> a >> b;
    vector<vector<bool>> dp(2, vector<bool>(t + 1));
    dp[0][0] = 1, dp[1][0] = 1;
    for (int i = 0; i <= t; i++) {
        for (int j : vector<int>{a, b}) {
            if (i >= j && dp[0][i - j]) dp[0][i] = 1;
        }
        if (dp[0][i]) dp[1][i / 2] = 1;
    }
    for (int i = 0; i <= t; i++) {
        for (int j : vector<int>{a, b}) {
            if (i >= j && dp[1][i - j]) dp[1][i] = 1;
        }
    }
    for (int i = t; i >= 0; i--) {
        if (dp[0][i] || dp[1][i]) {
            cout << i << "\n";
            return 0;
        }
    }
}
/*
Type: Knapsack DP
Algorithm:
Run Knapsack by simulating the eating of fruits
and drinking of water
NOTES:
Can't do all of this under one for loop; must initially
process the situations where you haven't drank water
*/