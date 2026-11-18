#include <bits/stdc++.h>
using namespace std;

const int n = 1e5 + 10; // constant
vector<int> adj[n]; // adjacency list
vector<int> visited(n);
void dfs(int node) {
    if (visited[node]) return;
    visited[node] = true;
    for (int i : adj[node]) {
        if (!visited[i]) dfs(i);
    }
}
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<int> bridges;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i); bridges.push_back(i);
        }
    }
    cout << bridges.size() - 1 << endl;
    for (int i = 0; i < bridges.size() - 1; i++) {
        cout << bridges[i] << " " << bridges[i + 1] << endl;
    }
}