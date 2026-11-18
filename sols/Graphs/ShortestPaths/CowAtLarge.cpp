#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

const int MAX = 1e5 + 1;
vector<int> adj[MAX];
int dists[MAX];
void dfs(int node, int prev, int dist) {
    dists[node] = dist;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node, dist + 1);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("atlarge.in", "r", stdin);
    freopen("atlarge.out", "w", stdout);
    int n, k; cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(k, -1, 0);
    queue<int> q;
    vector<int> dists2(n + 1, INT_MAX);
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() == 1) {
            q.push(i);
            vis[i] = 1;
            dists2[i] = 0;
        }
    }
    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int i : adj[v]) {
            if (!vis[i]) {
                vis[i] = 1;
                dists2[i] = dists2[v] + 1;
                q.push(i);
            }
        }
    }
    int cnt = 0;
    q.push(k);
    fill(begin(vis), end(vis), 0);
    vis[k] = 1;
    while (!q.empty()) {
        int v = q.front(); q.pop();
        if (dists[v] >= dists2[v]) {
            ++cnt; continue;
        }
        for (int i : adj[v]) {
            if (!vis[i]) {
                vis[i] = 1;
                q.push(i);
            }
        }
    }
    cout << cnt << '\n';
}
/*
Observation 1:
Bessie can only be stopped
if the minimum distance from
a placed farmer is <= her 
distance from a node.

Observation 2:
One farmer can guard a
subtree of nodes, with the
root being where Bessie and
the farmer will intersect.

Observation 3:
It's always optimal to place one farmer
at an intersection (root of subtree).
*/