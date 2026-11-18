#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
template<class T> class FenwickTree {
    private:
        int sz; vector<T> arr;
    public:
        FenwickTree(int n) {
            sz = n + 1, arr.resize(n + 1);
        }
        FenwickTree() {} // empty init
        T prefix(int idx) {
            T tot = 0;
            for (++idx; idx >= 1; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < sz; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pii>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back({--v, i});
        adj[v].push_back({u, i});
    }
    int timer = 0, LOG = 17;
    vector<int> tin(n), tout(n), 
                taken(n);
    vector up(LOG, vector(n, 0));
    auto tour = [&](int u, int p, auto&& tour) -> void {
        tin[u] = timer++;
        for (int i = 1; i < LOG; i++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }
        for (auto [v, id] : adj[u]) if (v != p) {
            up[0][v] = u, taken[v] = id;
            tour(v, u, tour);
        }
        tout[u] = timer - 1;
    }; tour(0, -1, tour);
    auto isAncestor = [&](int a, int b) -> bool {
        return tin[a] <= tin[b] && tout[a] >= tout[b];
    };
    auto lca = [&](int u, int v) -> int {
        if (isAncestor(u, v)) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (!isAncestor(up[i][u], v)) {
                u = up[i][u];
            }
        }
        return up[0][u];
    };
    FenwickTree<int> added(timer);
    for (int i = 0; i < m; i++) {
        int z; cin >> z;
        vector<int> cur(z);
        for (int &i : cur) {
            cin >> i, --i;
        }
        sort(all(cur), [&](int x, int y) {
            return tin[x] < tin[y];
        });
        cur.push_back(cur[0]);
        for (int j = 0; j < z; j++) {
            int anc = lca(cur[j], cur[j + 1]);
            added.update(tin[cur[j]], 1);
            added.update(tin[cur[j + 1]], 1);
            added.update(tin[anc], -2);
        }
    }
    vector<int> res;
    for (int i = 1; i < n; i++) {
        if (added.query(tin[i], tout[i]) >= k * 2) {
            res.push_back(taken[i]);
        }
    }
    sort(all(res));
    cout << sz(res) << "\n";
    for (int i = 0; i < sz(res); i++) {
        cout << res[i] << " \n"[i == sz(res) - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Railway (BOI)
 * For each deputy minister:
 * Note that if we sort the nodes by their Euler Tour "start"
 * time and loop back at the end, that we do our entire traversal
 * in the correct order (while using each edge twice). For every
 * pair of nodes in the traversal then, increment them. However, any node
 * "above" or equal to the LCA will not have an edge, so then we subtract 2
 * at the LCA. Use a fenwick tree to do this.
*/