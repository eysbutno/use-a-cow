#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 2e5 + 1;
const int LOG = 19;
vector<int> adj[N];
int up[2][LOG][N], dep[2][N];
void dfs(int node, int prev, int id) {
    up[id][0][node] = prev;
    for (int i = 1; i < LOG; i++) {
        int ans = up[id][i - 1][node];
        up[id][i][node] = up[id][i - 1][ans];
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dep[id][i] = dep[id][node] + 1;
            dfs(i, node, id);
        }
    }
}
int jump(int x, int d, int id) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (1 & (d >> i)) {
            x = up[id][i][x];
        }
    }
    return (x > 0 ? x : -1);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1, 0, 0);
    int bst = 1;
    for (int i = 2; i <= n; i++) {
        if (dep[0][i] > dep[0][bst]) {
            bst = i;
        }
    }
    dfs(bst, 0, 0);
    bst = 1;
    for (int i = 2; i <= n; i++) {
        if (dep[0][i] > dep[0][bst]) {
            bst = i;
        }
    }
    dfs(bst, 0, 1);
    int q; cin >> q;
    while (q--) {
        int u, d; cin >> u >> d;
        cout << max(jump(u, d, 0),
            jump(u, d, 1)) << '\n';
    }
}
/**
 * Longest path from
 * one node to another is 
 * on either diameter. So,
 * just perform LCA on both
 * endpoints of the diameters.
*/