#include <bits/stdc++.h>
using namespace std;
 
int furthest, dis = -1;
vector<vector<int>> adj;
void dfs(int node, int prev, int dist) {
    if (dis < dist) {
        dis = dist, furthest = node;
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node, dist + 1);
        }
    }
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    int n; cin >> n;
    int idx = n;
    adj.resize(n + 1);
    while (--idx) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1, 0);
    dis = 0;
    dfs(furthest, -1, 0);
    cout << dis << "\n";
}
/*
Type: DFS
Algorithm: Find the furthest node
from the root node, and then find the farthest node 
from that node.
*/