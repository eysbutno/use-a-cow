#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int MOD = 1e9 + 7;

int main() {
    int n, x; cin >> n >> x;
    vector<int> coins(n);
    for (int &i : coins) cin >> i;
    vector<ll> dp(x + 1);
    for (int i : coins) {
        if (i <= x) dp[i]++;
    }
    for (int i = 0; i <= x; i++) {
        for (int j : coins) {
            if (i - j >= 0) {
                dp[i] += dp[i - j];
                dp[i] %= MOD;
            }
        }
    }
    cout << dp[x] << "\n";
}