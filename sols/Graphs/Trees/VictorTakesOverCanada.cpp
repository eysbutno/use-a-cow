#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
template<typename T> class FenwickTree {
    private:
        int n; vector<T> arr;
    public:
        FenwickTree(int _n) : n(_n + 1) {
            arr.resize(n);
        }
        T prefix(int idx) { // [0, idx] sum
            T tot = 0;
            for (++idx; idx > 0; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        T query(int l, int r) { // [l, r] sum
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < n; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
void solve() {
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> c(n);
    for (int &i : c) {
        cin >> i, --i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<int> tin(n), tout(n);
    const int LOG = 32 - __builtin_clz(n);
    vector up(LOG, vector(n, 0));
    int timer = 0;
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        tin[u] = timer++;
        up[0][u] = p;
        for (int i = 1; i < LOG; i++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
        }
        tout[u] = timer - 1;
    }; dfs(0, 0, dfs);
    auto isAnc = [&](int u, int v) -> bool {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    };
    auto lca = [&](int u, int v) -> int {
        if (isAnc(u, v)) return u;
        if (isAnc(v, u)) return v;
        for (int i = LOG - 1; i >= 0; i--) {
            if (!isAnc(up[i][u], v)) u = up[i][u];
        }
        return up[0][u];
    };
    vector<set<pii>> ind(k);
    for (int i = 0; i < n; i++) {
        ind[c[i]].insert({tin[i], i});
    }
    FenwickTree<int> ft(n);
    for (auto &cur : ind) {
        int prv = -1;
        for (auto [loc, idx] : cur) {
            ft.update(loc, 1);
            if (prv != -1) {
                ft.update(tin[lca(prv, idx)], -1);
            }
            prv = idx;
        }
    }
    auto apply = [&](int c, int u, int dx) -> void {
        auto it = ind[c].lower_bound({tin[u], -1});
        vector<int> seen;
        if (it != end(ind[c])) {
            auto [_, t] = *it;
            ft.update(tin[lca(t, u)], dx);
            seen.push_back(t);
        }
        if (it != begin(ind[c])) {
            auto [_, t] = *prev(it);
            ft.update(tin[lca(t, u)], dx);
            seen.push_back(t);
        }
        if (sz(seen) == 2) {
            ft.update(tin[lca(seen[0], seen[1])], -dx);
        }
    };
    auto upd = [&]() -> void {
        int city, rep;
        cin >> city >> rep;
        --city, --rep;
        if (c[city] == rep) return;
        ind[c[city]].erase({tin[city], city});
        apply(c[city], city, 1);
        apply(rep, city, -1);
        ind[rep].insert({tin[city], city});
        c[city] = rep;
    };
    auto qry = [&]() -> void {
        int u; cin >> u; --u;
        cout << ft.query(tin[u], tout[u]) << "\n";
    };
    while (q--) {
        int t; cin >> t;
        (t > 1) ? qry() : upd();
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: DMOPC P5 - Victor Takes Over Canada.
 * Let an array a be the sorted Euler Tour visit time indices
 * for a particular guard. Obviously, each indice contributes 1 to
 * any subtree that has it. However, we need to take care of duplicates.
 * Observe that lca(a_i-1, a_i+1) is either lca(a_i-1, a_i) or lca(a_i, a_i+1).
 * Therefore, by induction, if we subtract 1 from lca(a_i-1, a_i), and later
 * subtract 1 from lca(a_i, a_i+1), then lca(a_i-1, a_i - 1) MUST be covered.
*/