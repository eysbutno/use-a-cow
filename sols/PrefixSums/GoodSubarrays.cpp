#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve() {
    int n; cin >> n;
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        dp[i] = (c - '0') + dp[i - 1];
    }
    map<int, ll> m;
    for (int i = 0; i <= n; i++) {
        m[dp[i] - i]++;
    }
    ll ans = 0;
    for (const auto& [f, i] : m) {
        ans += i * (i - 1) / 2;
    }
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}