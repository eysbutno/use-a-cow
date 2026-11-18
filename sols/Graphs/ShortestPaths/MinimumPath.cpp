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
    int n, m;
    cin >> n >> m;
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    const ll INF = 1e18;
    vector dist(n, vector(2, vector(2, INF)));
    // [vertex][if taken max edge][if taken min edge]
    priority_queue<array<ll, 4>> pq;
    pq.push({0, 0, 0, 0});
    dist[0][0][0] = 0;
    while (!pq.empty()) {
        auto [t, u, b1, b2] = pq.top(); pq.pop();
        if ((t *= -1) > dist[u][b1][b2]) continue;
        for (auto [v, w] : adj[u]) {
            for (int i = 0; i < 2; i++) {
                for (int j = 0; j < 2; j++) {
                    if (b1 > i || b2 > j) continue;
                    ll nt = t + w + (b1 < i ? -w : 0) 
                                  + (b2 < j ? w : 0);
                    if (smin(dist[v][i][j], nt)) {
                        pq.push({-nt, v, i, j});
                    }
                }
            }
        }
    }
    for (int i = 1; i < n; i++) {
        cout << dist[i][1][1] << " \n"[i == n - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * If we transform the problem so that we can
 * choose ANY edge, then naturally, to minimize the path,
 * the chosen edges MUST be max(w_e_i) and min(w_e_i).
*/