#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5 + 1;
const int LOG = 18;
vector<int> adj[N];
int st[N], ed[N], e[N], 
    up[LOG][N], dep[N], t;
template<class T> class FT {
    private:
        int sz;
        vector<T> pf;
    public:
        FT(int n) {
            sz = n + 1;
            pf.resize(n + 1);
        }
        T prefix(int idx) {
            ++idx; 
            T tot = 0;
            while (idx >= 1) {
                tot ^= pf[idx];
                idx -= idx & -idx;
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) ^ prefix(l - 1);
        }
        void update(int idx, T val) {
            ++idx;
            while (idx <= sz) {
                pf[idx] ^= val;
                idx += idx & -idx;
            }
        }
};
void tour(int node, int prev) {
    st[node] = t++;
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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("cowland.in", "r", stdin);
    freopen("cowland.out", "w", stdout);
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
    FT<int> bit(n + 2);
    for (int i = 1; i <= n; i++) {
        bit.update(st[i], e[i]);
        bit.update(ed[i], e[i]);
        // XOR inverts itself
    }
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            // undo the previous element
            bit.update(st[x], e[x]);
            bit.update(ed[x], e[x]);
            bit.update(st[x], y);
            bit.update(ed[x], y);
            e[x] = y;
        } else {
            // path queries problem, but with LCA
            int anc = lca(x, y);
            cout << (bit.query(st[anc], st[x]) 
                ^ bit.query(st[anc], st[y]) 
                ^ e[anc]) << '\n';
        }
    }
}
/**
 * Algorithm:
 * Using the strategy to find
 * the sum of a path, but using
 * LCA to handle the less nice
 * cases.
 * 
 * Uses: Fenwick Tree, Euler Tour,
 * and LCA (using binary jumping)
*/