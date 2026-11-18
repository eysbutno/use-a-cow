#include <bits/stdc++.h>
using namespace std;
 
const int MAX = 2e5 + 1;
int dist[MAX][2], res, dis = -1;
vector<int> adj[MAX];
void dfs(int node, int prev, int d, int id) {
    dist[node][id] = d;
    if (d > dis) {
        dis = d, res = node;
    }
    for (int i : adj[node]) {
        if (i != prev) dfs(i, node, d + 1, id);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1, 0, 0);
    dis = -1;
    dfs(res, -1, 0, 0);
    dis = -1;
    dfs(res, -1, 0, 1);
    for (int i = 1; i <= n; i++) {
        cout << max(dist[i][0], dist[i][1]) << ' ';
    }
}