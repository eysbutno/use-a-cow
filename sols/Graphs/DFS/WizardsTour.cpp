#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define f first 
#define s second 

const int MAX = 2e5 + 1;
vector<pii> adj[MAX];
vector<vector<int>> ans;
int vis[MAX], timer = 0;
bool used[MAX];
void dfs(int node, int prev, int id) {
    vis[node] = ++timer;
    vector<int> avail;
    for (pii& i : adj[node]) {
        if (vis[i.f] < vis[node] &&
            vis[i.f] && i.f != prev) {
            avail.pb(i.f);
            used[i.s] = 1;
        } else if (!vis[i.f]) {
            dfs(i.f, node, i.s);
            if (!used[i.s]) {
                avail.pb(i.f);
                used[i.s] = 1;               
            }
        }
    }
    int sz = size(avail);
    for (int i = 1; i < sz; i += 2) {
        ans.pb({avail[i - 1], node, avail[i]});
    }
    if (sz % 2 && id != -1) {
        ans.pb({avail.back(), node, prev});
        used[id] = 1;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb({y, i});
        adj[y].pb({x, i});
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i, -1, -1);
    }
    cout << size(ans) << '\n';
    for (auto& i : ans) {
        for (int j : i) {
            cout << j << ' ';
        }
        cout << '\n';
    }
}
/*
Observation 1:
This problem can be expressed
as finding the maximum ways
you can have pairs of adjacent edges,
where each edge is only used in one pair.

Observation 2:
You can use the DFS tree, and arbitrarily 
arrange the pairings.

The pairings will work like this:
Leaf-parent edges will always be
created, and will be linked with its
parents other pairs. Once that runs out,
any remaining ones get paired with the parent node.

Observation 3:
Because the DFS tree simplifies the graph's
structure, you can always achieve an optimal
solution by simply treating back edges
like a leaf node, aka forcefully connecting
them to the current nodes.
*/