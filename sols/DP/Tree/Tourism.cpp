#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, m; 
    cin >> n >> m;
    vector<ll> w(n);
    for (ll &i : w) cin >> i;
    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    int st; cin >> st; --st;
    vector<int> depth(n), highest(n);
    vector<bool> hasCycle(n), vis(n);
    auto dfs1 = [&](int u, int p, auto&& dfs1) -> void {
        highest[u] = depth[u], vis[u] = true;
        for (int v : adj[u]) if (v != p) {
            if (vis[v]) {
                // not part of our subtree.
                smin(highest[u], depth[v]);
            } else {
                // in our subtree, so process.
                depth[v] = depth[u] + 1;
                dfs1(v, u, dfs1);
                if (hasCycle[v]) {
                    hasCycle[u] = true;
                }
                smin(highest[u], highest[v]);
            }
        }
        if (highest[u] < depth[u]) {
            // if there is a backedge to somewhere higher.
            hasCycle[u] = true;
        }
    }; dfs1(st, -1, dfs1);
    vector<array<ll, 2>> dp(n, {0, 0});
    // dp[i][0] = max sum if we don't go down this subtree.
    // dp[i][1] = max sum if we go down this subtree.
    fill(all(vis), false);
    auto dfs2 = [&](int u, int p, auto&& dfs2) -> void {
        if (hasCycle[u]) dp[u][0] = w[u];
        dp[u][1] = w[u], vis[u] = true;
        ll free = w[u]; // stuff you don't go down.
        for (int v : adj[u]) if (v != p) {
            // can now ignore back edges.
            if (vis[v]) continue;
            dfs2(v, u, dfs2);
            dp[u][0] += dp[v][0];
            dp[u][1] += dp[v][0];
            smax(dp[u][1], free + dp[v][1]);
            free += dp[v][0];
        }
    }; dfs2(st, -1, dfs2);
    cout << dp[st][1] << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Tourism (CF)
 * Represent the graph as a DFS tree, and
 * check if a given subtree has a cycle within
 * it. Then, DP on each subtree. We maintain
 * two DPs: one for if we "go down" one of the
 * children, and one for if we don't.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/