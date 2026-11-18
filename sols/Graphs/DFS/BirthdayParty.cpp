#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj; 
vector<bool> visited;
bool done = 0;
void dfs(int node, int a, int b) {
    visited[node] = true;
    for (int i : adj[node]) {
        if (!visited[i]) {
            if (!(node == a && i == b)) {
                if (!(node == b && i == a)) {
                    dfs(i, a, b);
                }
            }
        }
    }
}
void solve() {
    int p, c; cin >> p >> c;
    if (!p && !c) {done = 1; return;}
    visited.resize(p); adj.resize(p);
    vector<pair<int, int>> connections(c);
    for (int i = 0; i < c; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        connections[i] = {a, b};
    }  
    bool possible = 0;
    for (auto i : connections) {
        dfs(0, i.first, i.second);
        for (bool j : visited) {
            if (!j) {possible = 1; break;}
        }
        for (int j = 0; j < p; j++) visited[j] = 0;
        if (possible) break;
    }
    adj.clear(); visited.clear();
    if (possible) cout << "Yes" << "\n";
    else cout << "No" << "\n";
}
int main() {
    for (int i = 0; i < 10; i++) {
        if (done) return 0;
        solve();
    }
}
/*
Type: DFS
Algorithm:
Just brute force each pair that could lose a #
*/