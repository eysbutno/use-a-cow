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
vector<pii> adj[N];
int st[N], ed[N], e[N], 
    up[LOG][N], dep[N], t;
void tour(int node, int prev) {
    st[node] = t++;
    up[0][node] = prev;
    for (int i = 1; i < LOG; i++) {
        int ans = up[i - 1][node];
        up[i][node] = up[i - 1][ans];
    }
    for (auto& i : adj[node]) {
        if (i.f != prev) {
            dep[i.f] = dep[node] + 1;
            e[i.f] = i.s;
            tour(i.f, node);
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
                tot += pf[idx];
                idx -= idx & -idx;
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            ++idx;
            while (idx <= sz) {
                pf[idx] += dx;
                idx += idx & -idx;
            }
        }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<pii> con(n);
    for (int i = 1; i < n; i++) {
        int x, y, w; 
        cin >> x >> y >> w;
        adj[x].pb({y, w});
        adj[y].pb({x, w});
        con[i] = {x, y};
    }
    tour(1, 0);
    FT<ll> bit(n + 5);
    for (int i = 1; i <= n; i++) {
        bit.update(st[i], e[i]);
        bit.update(ed[i], -e[i]);
        if (i != n && dep[con[i].f] 
            < dep[con[i].s]) {
            swap(con[i].f, con[i].s);
        }
    }
    int q; cin >> q;
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            int u = con[x].f;
            bit.update(st[u], y - e[u]);
            bit.update(ed[u], e[u] - y);
            e[u] = y;
        } else {
            int anc = lca(x, y);
            cout << (bit.query(0, st[x]) +
                bit.query(0, st[y]) - 2LL *
                bit.query(0, st[anc])) << '\n';
        }
    }
}
/**
 * Problem: Distance Queries on a Tree.
 * Idea: This is basically the normal
 * path query problem, except you just
 * shift the edge weight to the node
 * with the higher depth.
 * 
 * NOTE: You have to use the "standard"
 * formula for distances in this problem.
 * Why? IDK. But the less annoying way
 * doesn't work in this case.
*/