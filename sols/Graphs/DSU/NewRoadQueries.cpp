#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 2e5 + 1;
const int LOG = 19;
vector<pii> adj[N];
int up[LOG][N], mx[LOG][N], dep[N];
void dfs(int node, int prev) {
    for (int i = 1; i < LOG; i++) {
        int ans = up[i - 1][node];
        up[i][node] = up[i - 1][ans];
        mx[i][node] = max(mx[i - 1][node],
            mx[i - 1][up[i - 1][node]]);
    }
    for (auto [u, w] : adj[node]) {
        if (u != prev) {
            dep[u] = dep[node] + 1;
            mx[0][u] = w;
            up[0][u] = node;
            dfs(u, node);
        }
    }
}
int query(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    int d = dep[u] - dep[v], res = 0;
    for (int i = LOG - 1; i >= 0; i--) {
        if (1 & (d >> i)) {
            smax(res, mx[i][u]);
            u = up[i][u];
        }
    }
    if (u == v) return res;
    for (int i = LOG - 1; i >= 0; i--) {
        int u1 = up[i][u], v1 = up[i][v];
        if (u1 != v1) {
            smax(res, mx[i][u]);
            smax(res, mx[i][v]);
            u = u1, v = v1;
        }
    }
    return max({res, mx[0][u], mx[0][v]});
}
struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool con(int x, int y) {
        return get(x) == get(y);
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m, q;
    cin >> n >> m >> q;
    DSU dsu(n + 1);
    for (int i = 1; i <= m; i++) {
        int u, v; 
        cin >> u >> v;
        if (dsu.unite(u, v)) {
            adj[u].pb({v, i});
            adj[v].pb({u, i});
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!mx[0][i]) dfs(i, 0);
    }
    while (q--) {
        int x, y; cin >> x >> y;
        if (!dsu.con(x, y)) {
            cout << -1;
        } else {
            cout << query(x, y);
        }
        cout << '\n';
    }
}
/**
 * Problem: New Roads Queries.
 * Solution Idea: 
 * Construct a graph, with the time
 * the edge is created being the weight
 * of the graph. Find the maximum path
 * necessary to reach the destination.
 * 
 * Graph is a MBST, which is a tree.
 * So, you can use binary jumping
 * to store the max value of an edge,
 * when performing LCA.
 * 
 * NOTES:
 * - The query is done with LCA,
 *   during the jumping process.
 * - The edge path mustn't include 
 *   the LCA. This isn't an issue
 *   because of how mx[i][j] is
 *   calculated.
*/