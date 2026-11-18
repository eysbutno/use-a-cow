#include <bits/stdc++.h>
using namespace std;
using ll = long long;
// I LOVE CASWORK!!!!!!!!
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, s; cin >> n >> s;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    const int LOG = __lg(n) + 1;
    vector lift(LOG, vector(n + 1, 0));
    vector<int> tin(n + 1), tout(n + 1), dep(n + 1);
    int timer = 0;
    auto tour = [&](int u, int p, auto&& tour) -> void {
        tin[u] = timer++;
        lift[0][u] = p;
        dep[u] = dep[p] + 1;
        for (int i = 1; i < LOG; i++) {
            lift[i][u] = lift[i - 1][lift[i - 1][u]];
        }
        for (int v : adj[u]) {
            if (v != p) tour(v, u, tour);
        }
        tout[u] = timer - 1;
    };
    tour(1, 0, tour);
    tin[0] = -1, tout[0] = n + 1;
    auto isAnc = [&](int u, int v) -> bool {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    };
    auto lca = [&](int u, int v) -> int {
        if (isAnc(u, v)) return u;
        if (isAnc(v, u)) return v;
        for (int i = LOG - 1; i >= 0; i--) {
            if (!isAnc(lift[i][u], v)) {
                u = lift[i][u];
            }
        }
        return lift[0][u];
    };
    auto dist = [&](int a, int b, int anc = -1) -> int {
        if (anc == -1) anc = lca(a, b);
        return dep[a] + dep[b] - 2 * dep[anc];
    };
    vector<array<ll, 2>> diff(n + 1, {0, 0});
    auto upd = [&](int u, int v, int st, int dx) -> void {
        diff[u][0] += st, diff[u][1] += dx, diff[v][1] -= dx;
        if (dx > 0) {
            diff[v][0] -= st + (dep[u] - dep[v]);
        } else {
            diff[v][0] -= st - (dep[u] - dep[v]);
        }
    };
    auto qry = [&](int a, int b, int t) -> void {
        int par = lca(a, b);
        if (par == t || !isAnc(par, t)) {
            if (par == a || par == b) {
                if (par == a) swap(a, b);
                upd(a, lift[0][b], dist(a, t), -1);
            } else {
                upd(a, par, dist(a, t), -1);
                upd(b, lift[0][par], dist(b, t), -1);
            }
        } else {
            int l1 = lca(a, t), l2 = lca(b, t);
            if (par == a || par == b) {
                if (par == a) {
                    swap(a, b), swap(l1, l2);
                }
                upd(a, l1, dist(a, t, l1), -1);
                upd(l1, lift[0][b], dist(t, l1, l1), 1);
            } else if (l1 == par && l2 == par) {
                upd(a, par, dist(a, t, par), -1);
                upd(b, lift[0][par], dist(b, t, par), -1);
            } else {
                if (dep[l1] < dep[l2]) {
                    swap(l1, l2), swap(a, b);
                }
                upd(a, l1, dist(a, t, l1), -1);
                upd(l1, par, dist(l1, t, l1), 1);
                upd(b, lift[0][par], dist(b, t, par), -1);
            }
        }
    };
    while (s--) {
        int a, b, t;
        cin >> a >> b >> t;
        qry(a, b, t);
    }
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u, dfs);
            diff[u][0] += diff[v][0] + diff[v][1];
            diff[u][1] += diff[v][1];
        }
    };
    dfs(1, 0, dfs);
    for (int i = 1; i <= n; i++) {
        cout << diff[i][0] << " \n"[i == n];
    }
}