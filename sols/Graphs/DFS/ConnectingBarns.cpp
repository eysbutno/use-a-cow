#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll cost(int cmp1, int cmp2, vector<vector<int>>& comps) {
    int dist = 1e9;
    for (int i : comps[cmp1]) {
        int idx = upper_bound(begin(comps[cmp2]), 
            end(comps[cmp2]), i) - begin(comps[cmp2]);
        if (idx != comps[cmp2].size()) {
            dist = min(dist, abs(i - comps[cmp2][idx]));
        }
        if (idx != 0) {
            dist = min(dist, abs(comps[cmp2][idx - 1] - i));
        }
    }
    return (ll) dist * dist;
}
void dfs(int node, int col, vector<vector<int>>& graph, vector<int>& group) {
    group[node] = col;
    for (int i : graph[node]) {
        if (!group[i]) dfs(i, col, graph, group);
    }
}
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    while (m--) {
        int i, j; cin >> i >> j;
        adj[i].push_back(j);
        adj[j].push_back(i);
    }
    vector<int> color(n + 1); int id = 0;
    for (int i = 1; i <= n; i++) {
        if (!color[i]) dfs(i, ++id, adj, color);
    }
    vector<vector<int>> comps(id + 1);
    for (int i = 1; i <= n; i++) {
        comps[color[i]].push_back(i);
    }
    ll ans = cost(color[1], color[n], comps);
    for (int i = 1; i <= id; i++) {
        ans = min(ans, cost(i, color[1], comps) + cost(i, color[n], comps));
    }
    cout << ans << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}
/*
Type: Binary Search, DFS
Algorithm:
Create a vector of all the connected components.
Calculate the max cost for using **a certain COMPONENT**
as an intermediate for the two barns.
NOTE: DON'T CALCULATE IT FOR EVERY BARN IN BETWEEN!
*/