#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj; // adjacency list
vector<int> visited;
vector<bool> team;
int n, m; bool bad = 0;
void dfs(int node) {
    if (bad) return;
    visited[node] = true;
    for (int i : adj[node]) {
        if (visited[i]) {
            if (team[i] == team[node]) {
                bad = 1; return;
            }
            continue;
        }
        team[i] = !team[node];
        dfs(i);
    }
}
int main() {
    int n, m; cin >> n >> m;
    adj.resize(n + 1); team.resize(n + 1); visited.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 1; i <= n; i++) if (!visited[i]) dfs(i);
    if (bad) {cout << "IMPOSSIBLE" << endl; return 0;}
    for (int i = 1; i <= n; i++) {
        cout << (int) team[i] + 1 << " ";
    }
    return 0;
}