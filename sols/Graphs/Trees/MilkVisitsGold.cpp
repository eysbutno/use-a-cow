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

const int N = 1e5 + 1;
const int LOG = 18;
vector<int> adj[N];
vector<int> poi[2][N];
int st[N], ed[N], e[N], 
    up[LOG][N], dep[N], t;
void tour(int node, int prev) {
    st[node] = t++;
    poi[0][e[node]].pb(t - 1);
    up[0][node] = prev;
    for (int i = 1; i < LOG; i++) {
        int ans = up[i - 1][node];
        up[i][node] = up[i - 1][ans];
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dep[i] = dep[node] + 1;
            tour(i, node);
        }
    }
    ed[node] = t;
    poi[1][e[node]].pb(t - 1);
}
int jump(int x, int d) {
    for (int i = LOG - 1; i >= 0; i--) {
        if (1 & (d >> i)) {
            x = up[i][x];
        }
    }
    return x;
}
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }
    u = jump(u, dep[u] - dep[v]);
    if (u == v) return u;
    for (int i = LOG - 1; i >= 0; i--) {
        int u1 = up[i][u], v1 = up[i][v];
        if (u1 != v1) u = u1, v = v1;
    }
    return up[0][u];
}
int query(int l, int r, vector<int>& a) {
    // count number of occurences in
    // the interval [l, r].
    int idx1 = upper_bound(all(a), r) - begin(a) - 1;
    int idx2 = lower_bound(all(a), l) - begin(a);
    return idx1 - idx2 + 1;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> e[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    tour(1, 0);
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        int anc = lca(a, b);
        if (query(st[anc], st[a], poi[0][c]) > 
            query(st[anc], st[a] - 1, poi[1][c])) {
            cout << 1;
        } 
        else if (query(st[anc], st[b], poi[0][c])
            > query(st[anc], st[b] - 1, poi[1][c])) {
            cout << 1;
        }
        else {
            cout << 0;
        }
    }
    cout << '\n';
}
/**
 * Probably will use a similar
 * idea to the problem "Cow Land".
 * No updates are performed, so
 * PURQ DS is probably not needed.
 * 
 * Algorithm:
 * For a path, you can mark the number
 * of start and end occurences among
 * the subtree. 
 * 
 * The main concern is if, between the
 * path from the LCA to the node, there's
 * another instance of the target milk.
 * However, if we track the end times,
 * it's a non-issue.
 * 
 * Implementation Details:
 * 1. Uses lower bound to query # of
 * indices between a left and right bound
 * 2. When querying the end times, we exclude
 * the current node because we don't care about 
 * any end times ending on the starting node.
*/