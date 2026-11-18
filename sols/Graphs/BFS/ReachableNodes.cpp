#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; 
    cin >> n >> m;
    vector<int> deg(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[--v].push_back(--u);
        ++deg[u];
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!deg[i]) q.push(i);
    }
    vector<bitset<50'000>> dp(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        dp[u][u] = 1;
        for (int v : g[u]) {
            dp[v] |= dp[u];
            if (!(--deg[v])) {
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dp[i].count() << " \n"[i == n - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    solve();
}
/**
 * TASK: Reachable Nodes.
 * Toposort + Bitset cheese.
*/