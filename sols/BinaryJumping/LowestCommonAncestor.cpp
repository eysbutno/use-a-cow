#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 1, LOG = 17;
int up[LOG + 1][MAX], depth[MAX];
vector<int> adj[MAX];
void dfs(int node, int prev, int dist) {
    depth[node] = dist;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node, dist + 1);
            up[0][i] = node;
        }
    }
}
int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    int dist = depth[x] - depth[y];
    for (int i = LOG; i >= 0; i--) {
        int power = pow(2, i);
        if (dist >= power) {
            x = up[i][x];
            dist -= power;
        }
    }
    if (x == y) return x;
    for (int i = LOG; i >= 0; i--) {
        if (up[i][x] != up[i][y]) {
            x = up[i][x], y = up[i][y];
        }
    }
    return up[0][x];
}
int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);
    int n, q; cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1, 0);
    for (int i = 1; i <= LOG; i++) {
        for (int j = 2; j <= n; j++) {
            up[i][j] = up[i - 1][up[i - 1][j]];
        }
    }
    while (q--) {
        int x, y; cin >> x >> y;
        cout << lca(x, y) << "\n";
    }
}