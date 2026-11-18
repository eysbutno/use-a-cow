#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("teamwork.in", "r", stdin);
    freopen("teamwork.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<int> c(n);
    for (int& i : c) {
        cin >> i;
    }
    vector<int> dp(n);
    for (int i = 0; i < n; i++) {
        int mx = 0, base = 0;
        if (i > 0) base = dp[i - 1];
        for (int j = i; j < min(n, i + k); j++) {
            mx = max(mx, c[j]);
            dp[j] = max(dp[j], (j - i + 1) * mx + base);
        }
    }
    cout << dp.back() << '\n';
}
/**
 * dp[i] = max sum, up to team i
 * Just process each possible starting
 * point for a team, in order.
*/