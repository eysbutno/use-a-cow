#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

#ifdef LOCAL
#include "../src/debug.hpp"
#else
#define debug(...) 420
#endif
// g++ -DLOCAL -Wall Practice.cpp -o bin

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n; ll x, y;
    cin >> n >> x >> y;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    if (x >= y) { // non-tree edges are good
        int mx = 0;
        for (int i = 0; i < n; i++) {
            smax(mx, sz(adj[i]));
        }
        cout << ((n - 2) * y + (mx == n - 1 ? x : y)) << "\n";
    } else { // the other case...
        vector<array<int, 2>> dp(n);
        // [0 / 1]: if path continues & goes up
        auto dfs = [&](int u, int p, auto &&self) -> void {
            int d1 = n + 5, d2 = n + 5, sum = 0;
            for (int v : adj[u]) {
                if (v == p) continue;
                self(v, u, self);
                sum += dp[v][0];
                int dx = dp[v][1] - dp[v][0];
                if (dx < d1) {
                    d2 = d1, d1 = dx;
                } else if (dx < d2) {
                    d2 = dx;
                }
            }
            dp[u][1] = min(sum + 1, sum + d1);
            dp[u][0] = min(dp[u][1], sum + d1 + d2 - 1);
        };
        dfs(0, -1, dfs);
        cout << (x * (n - dp[0][0]) + y * (dp[0][0] - 1)) << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Case 1: x >= y
 * Other than a star graph, you can always use
 * as many non-tree edges as you want.
 * 
 * Case 2: x < y
 * Let dp[u][0 / 1] be minimum non-tree edges to visit
 * every node in the subtree of u. The second dimension 
 * represents if we go back up to the root or not.
*/