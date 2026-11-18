#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<bool> visited;
void dfs(int node, int rel) {
    visited[node] = true;
    for (auto i : adj[node]) {
        int a = i.first, b = i.second;
        if (!visited[a] && b >= rel) {
            dfs(a, rel);
        }
    }
}
int main() {
    int n, q; cin >> n >> q;
    adj.resize(n + 1);
    visited.resize(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int p, q, r; cin >> p >> q >> r;
        adj[p].push_back({q, r});
        adj[q].push_back({p, r});
    }
    for (int i = 0; i < q; i++) {
        int k, v; cin >> k >> v;
        dfs(v, k); int count = -1;
        for (int j = 1; j <= n; j++) {
            count += (int) visited[j];
            visited[j] = false;
        }
        cout << count << "\n";
    }
    return 0;
}
/*
Just keep on running DFS
*/