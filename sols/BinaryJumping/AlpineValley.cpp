#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;

void solve() {
    int n, s, q, e;
    cin >> n >> s >> q >> e; --e;
    vector<vector<pii>> adj(n);
    vector<array<int, 3>> edges(n - 1);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
        edges[i - 1] = {u, v, w};
    }
    const ll INF = 1e18;
    vector<ll> dp(n, INF), dist(n);
    for (int i = 0; i < s; i++) {
        int c; cin >> c;
        dp[--c] = 0ll;
    }
    const int LOG = 32 - __builtin_clz(n);
    vector lift(LOG, vector(n, 0));
    vector data(LOG, vector(n, INF));
    vector<int> dep(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        for (auto [v, w] : adj[u]) if (v != p) {
            dist[v] = dist[u] + w;
            dep[v] = dep[u] + 1;
            lift[0][v] = u;
            for (int i = 1; i < LOG; i++) {
                lift[i][v] = lift[i - 1][lift[i - 1][v]];
            }
            dfs(v, u, dfs);
            dp[u] = min(dp[u], dp[v] + w);
        }
    }; dfs(e, -1, dfs);
    auto dfs2 = [&](int u, int p, auto&& dfs2) -> void {
        for (auto [v, w] : adj[u]) if (v != p) {
            data[0][v] = dp[u] - dist[u];
            for (int i = 1; i < LOG; i++) {
                data[i][v] = min(data[i - 1][v], data[i - 1][lift[i - 1][v]]);
            }
            dfs2(v, u, dfs2);
        }
    }; dfs2(e, -1, dfs2);
    for (auto &[u, v, w] : edges) {
        if (dep[u] > dep[v]) swap(u, v);
    }
    auto jump = [&](int x, int d) -> array<ll, 2> {
        array<ll, 2> res = {INF, x};
        for (int i = LOG - 1; i >= 0; i--) {
            if (d >> i & 1) {
                res[0] = min(res[0], data[i][res[1]]);
                res[1] = lift[i][res[1]];
            }
        }
        return res;
    };
    auto qry = [&](int idx, int r) -> void {
        int dx = dep[r] - dep[edges[idx][1]];
        array<ll, 2> res = (dx < 0 ? array<ll, 2>{0, 0} : jump(r, dx));
        if (dx < 0 || jump(r, dx)[1] != edges[idx][1]) {
            cout << "escaped" << "\n";
        } else {
            ll ans = min(res[0] + dist[r], dp[r]);
            cout << (ans < INF ? to_string(ans) : "oo") << "\n";
        }
    };
    while (q--) {
        int i, r;
        cin >> i >> r;
        qry(i - 1, r - 1);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Root the tree at E. Checking if you can escape
 * is pretty easy. To find the best shop route, just
 * maintain the fastest route to a route in the current
 * subtree, and maintain a binlift of the following value:
 * dp[v] - dist[v], and then binlift off of that.
 * For any given start, dist[v] + binlift(v) will return
 * the correct answer.
*/