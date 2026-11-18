#include <bits/stdc++.h>
using namespace std;

void dfs(int node, bool col, vector<bool>& vis,
    vector<vector<int>>& adj, set<int>& s) {
    if (vis[node]) return;
    vis[node] = 1;
    if (col) s.insert(node);
    for (int i : adj[node]) {
        dfs(i, !col, vis, adj, s);
    }
}
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    set<int> s1, s2;
    vector<bool> vis(n + 1);
    dfs(1, 0, vis, adj, s1);
    fill(begin(vis), end(vis), 0);
    dfs(1, 1, vis, adj, s2);
    if (size(s1) >= size(s2)) {
        cout << size(s2) << '\n';
        for (int i : s2) cout << i << ' ';
        cout << '\n';
    } else {
        cout << size(s1) << '\n';
        for (int i : s1) cout << i << ' ';
        cout << '\n';
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}
/*
Choose nodes in a bipartite fasion.
If starting with node 1 colored is
optimal, print that set out. Otherwise,
pick the other set.
*/