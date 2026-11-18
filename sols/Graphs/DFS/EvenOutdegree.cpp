#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define f first 
#define s second 

const int MAX = 1e5 + 1;
vector<int> adj[MAX];
vector<pii> ans;
int vis[MAX], deg[MAX], t = 0;
void dfs(int node, int prev) {
    vis[node] = ++t;
    for (int i : adj[node]) {
        if (vis[node] > vis[i] &&
            vis[i] && i != prev) {
            deg[node]++;
            ans.pb({node, i});
        } else if (!vis[i]) {
            dfs(i, node);
            if (deg[i] % 2) {
                deg[i]++;
                ans.pb({i, node});
            } else {
                deg[node]++;
                ans.pb({node, i});
            }
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i, -1);
    }
    for (int i = 1; i <= n; i++) {
        if (deg[i] % 2) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    for (pii& i : ans) {
        cout << i.f << ' ' 
            << i.s << '\n';
    }
}
/*
Uses the DFS tree
to solve the problem.
If the graph was a tree,
you'd just direct the leaf-edges
downwards, and then continue on.
To deal with back-edges, you just
direct them upwards... because that
works for some reason.

Note: a slight "justification" for
why directing the back-edges up works:
As a generalization, it leaves more 
"flexibility" and is less "problematic"
than directing them down, as directing
them down could cause some future issues.
*/