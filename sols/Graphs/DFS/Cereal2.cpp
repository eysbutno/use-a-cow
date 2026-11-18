#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, from, first;
};
void cycle(int node, int prev, int& f, int& skip,
    vector<vector<Edge>>& adj, vector<bool>& vis) {
    vis[node] = true;
    for (auto& i : adj[node]) {
        if (vis[i.to]) {
            if (i.to != prev && f == -1) {
                if (i.first) {
                    f = node;
                } else {
                    f = i.to;
                }
                skip = i.from;
            }
        } else {
            cycle(i.to, node, f, skip, adj, vis);
        }
    }
}
void dfs(int node, int skip, vector<bool>& taken, vector<int>& res,
    vector<bool>& vis, vector<vector<Edge>>& adj) {
    vis[node] = true;
    for (auto& i : adj[node]) {
        if (!vis[i.to] && i.from != skip) {
            res.push_back(i.from); taken[i.from] = 1;
            dfs(i.to, skip, taken, res, vis, adj);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<vector<Edge>> adj(m + 1);
    for (int i = 0; i < n; i++) {
        int f, s; cin >> f >> s; --f, --s;
        adj[f].push_back({s, i, 1});
        adj[s].push_back({f, i, 0});
    }
    vector<bool> vis(m), vis2(m), taken(n);
    vector<int> res;
    for (int i = 0; i < m; i++) {
        if (!vis[i]) {
            int f = -1, skip = -1;
            cycle(i, -1, f, skip, adj, vis2);
            if (f != -1 && skip != -1) {
                res.push_back(skip); taken[skip] = 1;
                dfs(f, skip, taken, res, vis, adj);
            } else {
                dfs(i, skip, taken, res, vis, adj);
            }
        }
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += taken[i];
        if (!taken[i]) {
            res.push_back(i);
        }
    }
    cout << n - cnt << '\n';
    for (int i : res) cout << i + 1 << '\n';
}
/*
For each connected component, we essentially start at
a given node and print out all the resulting nodes
from that starting node that will construct a minimum
spanning tree. If there's a cycle, we will construct a graph
with n nodes and n edges, and start inside the cycle. 
*/