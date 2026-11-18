#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second 

const int MAX = 1e5 + 1;
vector<pair<int, char>> adj[MAX];
bool type[MAX], vis[MAX], impossible = 0;
void dfs(int node, bool col) {
    if (impossible) return;
    vis[node] = 1; type[node] = col;
    for (auto i : adj[node]) {
        if (vis[i.f]) {
            if (i.s == 'S') {
                impossible = col != type[i.f];
            } else {
                impossible = col == type[i.f];
            }
        } else {
            if (i.s == 'S') {
                dfs(i.f, col);
            } else {
                dfs(i.f, !col);
            }
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        char t; int a, b;
        cin >> t >> a >> b;
        adj[a].push_back({b, t});
        adj[b].push_back({a, t});
    }
    int comps = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i, 1); comps++;
        }
    }
    if (impossible) {
        cout << 0;
    } else {
        cout << 1;
        while (comps--) cout << 0;
    }
}
/*
Type: DFS (Bipartite)
Algorithm:
To make life easier, we're using only 1 adjacency list
This is to remove the headache of potential intersections
All the checks are within each subtree
The algorithm counts connected components and if each
component is bipartite
*/