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
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    vector<vector<pii>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[--u].push_back({--v, w});
        adj[v].push_back({u, w});
    }
    const int LOG = 19;
    vector<ll> dpSelf(n), dpUp(n);
    vector up(LOG, vector(n, 0));
    vector<int> depth(n);
    auto dfs1 = [&](int u, int p,
                   auto&& dfs1) -> void {
        if (p != -1) up[0][u] = p;
        for (int i = 1; i < LOG; i++) {
            up[i][u] = up[i - 1][up[i - 1][u]];
        }
        dpSelf[u] = a[u];
        for (auto [v, w] : adj[u]) if (v != p) {
            depth[v] = depth[u] + 1;
            dfs1(v, u, dfs1);
            ll contrib = dpSelf[v] - 2LL * w;
            dpSelf[u] += max(contrib, 0LL);
        }
    }; dfs1(0, -1, dfs1);
    dpUp[0] = dpSelf[0];
    auto dfs2 = [&](int u, int p, 
                    auto&& dfs2) -> void {
        for (auto [v, w] : adj[u]) if (v != p) {
            dpUp[v] = dpUp[u] - max(0LL, dpSelf[v] - 2LL * w)
                    - w + dpSelf[v];
            dfs2(v, u, dfs2);
        }
    }; dfs2(0, -1, dfs2);
    auto dfs3 = [&](int u, int p,
                    auto&& dfs3) -> void {
        for (auto [v, w] : adj[u]) if (v != p) {
            ll contrib = max(0LL, dpSelf[v] - 2LL * w);
            ll dx = dpSelf[u] - contrib - 2LL * w;
            dpSelf[v] += max(0LL, dx);
            dfs3(v, u, dfs3);
        }
    }; dfs3(0, -1, dfs3);
    auto lca = [&](int u, int v) -> int {
        if (depth[u] < depth[v]) swap(u, v);
        for (int i = LOG - 1; i >= 0; i--) {
            if ((depth[u] - depth[v]) >> i & 1) {
                u = up[i][u];
            }
        }
        if (u == v) return u;
        for (int i = LOG - 1; i >= 0; i--) {
            if (up[i][u] != up[i][v]) {
                u = up[i][u], v = up[i][v];
            }
        }
        return up[0][u];
    };
    auto query = [&](int u, int v) -> ll {
        int anc = lca(u, v);
        return dpUp[u] + dpUp[v] - 2 * dpUp[anc] + dpSelf[anc];
    };
    while (q--) {
        int u, v; cin >> u >> v;
        cout << query(--u, --v) << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: G. Two Paths (CF)
 * Let dp_up[u] be the best p path from the root,
 * and dp[u] be the best p path from u -> u (downwards, then up).
 * Then, our answer for a given query is:
 * dp_up[u] + dp_up[v] - 2 * dp_up[lca] + dp[lca].
 * 
 * NOTE: We need to add back dp[lca], because subtracting
 * dp_up[lca] twice will subtract dp[lca] twice, even though
 * that's not correct. However, we still want to cover all the 
 * other "good" paths downwards from the LCA. Also, we don't need to
 * worry about if dp[lca] and dp_up[lca] go down either u or v's path. 
*/