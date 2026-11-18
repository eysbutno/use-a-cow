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
const ll INF = 1e18;
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[--u].push_back({--v, w});
        adj[v].push_back({u, w});
    }
    string vis(n, '0'); vis[0] = '1';
    vector<pair<string, ll>> res;
    priority_queue<array<ll, 2>> pq;
    for (auto [v, w] : adj[0]) {
        pq.push({-w, v});
    }
    ll cur = 0;
    while (!pq.empty() && vis.back() != '1') {
        auto [t, u] = pq.top(); pq.pop();
        if (vis[u] == '1') continue;
        assert(-t >= cur);
        res.push_back({vis, -t - cur});
        vis[u] = '1', cur = -t;
        for (auto [v, w] : adj[u]) {
            pq.push({t - w, v});
        }
    }
    if (vis.back() != '1') {
        cout << "inf" << "\n";
    } else {
        cout << cur << " " << sz(res) << "\n";
        for (auto &[fi, se] : res) {
            cout << fi << " " << se << "\n";
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Draw a weighted edge between u and v,
 * with weight y, and run Dijkstras on the graph.
 * The central idea is that we simply keep on adding animals
 * one by one, into the answer.
*/