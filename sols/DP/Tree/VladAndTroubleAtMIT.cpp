#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        adj[--p].push_back(i);
    }
    string s; cin >> s;
    vector<array<int, 3>> dp(n);
    const int INF = 1e9;
    auto dfs = [&](int u, auto&& dfs) -> void {
        dp[u] = {0, 0, 0};
        if (s[u] == 'P') {
            dp[u][0] = INF, dp[u][1] = INF;
        } else if (s[u] == 'S') {
            dp[u][0] = INF, dp[u][2] = INF;
        }
        for (int v : adj[u]) {
            dfs(v, dfs);
            dp[u][0] += min({dp[v][0], dp[v][1] + 1, dp[v][2] + 1});
            dp[u][1] += min({dp[v][0], dp[v][1], dp[v][2] + 1});
            dp[u][2] += min({dp[v][0], dp[v][1] + 1, dp[v][2]});
            for (int x = 0; x < 3; x++) {
                smin(dp[u][x], INF);
            }
        }
    }; dfs(0, dfs);
    cout << min({dp[0][0], dp[0][1], dp[0][2]}) << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * G. Vlad and Trouble at MIT (CF)
 * Do tree DP, and maintain the following DP
 * states:
 * 
 * dp[u][0]: this subtree does not care (no constraints)
 * dp[u][1]: there is a S student, somewhere in the subtree.
 * dp[u][2]: there is a P student, somewhere in the subtree.
*/