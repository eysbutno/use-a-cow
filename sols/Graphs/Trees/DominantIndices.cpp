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
void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<int> res(n);
    vector<pii> best(n);
    vector<map<int, int>> cur(n);
    auto merge = [&](int u, int v) -> void {
        smax(best[u], best[v]);
        if (sz(cur[u]) < sz(cur[v])) {
            swap(cur[u], cur[v]);
        }
        auto it = begin(cur[v]);
        while (it != end(cur[v])) {
            auto [dep, occ] = *it;
            cur[u][dep] += occ;
            smax(best[u], {cur[u][dep], -dep});
            it = cur[v].erase(it);
        }
    };
    auto dfs = [&](int u, int p, int d,
                   auto&& dfs) -> void {
        best[u] = {1, -d};
        cur[u][d] = 1;
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, d + 1, dfs);
            merge(u, v);
        }
        res[u] = -best[u][1] - d;
    }; dfs(0, -1, 0, dfs);
    for (int i = 0; i < n; i++) {
        cout << res[i] << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Originally thought you had to do some
 * funny stuff to make the depths correct when
 * merging subtrees... until I realized that you should
 * instead just store the "true" depth of the nodes when
 * small to large merging... 太强了
 * 
 * Anyways, then you would want to maintain the "best"
 * answer so far. The "best" answer would be the best
 * pair, such that {# of vertices, depth} is minimal.
*/