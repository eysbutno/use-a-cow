#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int) (x).size()
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 2e5;
void solve() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n);
    vector<int> inDeg(n);
    vector<pii> edges;
    for (int i = 0; i < m; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        adj[--x].pb({--y, t});
        if (t == 0) {
            adj[y].pb({x, t});
        } else {
            edges.pb({x, y});
            ++inDeg[y];
        }
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) q.push(i);
    }
    vector<int> toposort;
    vector<bool> vis(n);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        toposort.pb(u), vis[u] = 1;
        for (auto [v, t] : adj[u]) {
            if (t == 0 && !vis[v]) {
                edges.pb({u, v});
            } else {
                --inDeg[v];
                if (!inDeg[v]) {
                    q.push(v);
                }
            } 
        }
    }
    if (sz(toposort) != n) {
        cout << "NO" << '\n';
        return;
    }
    cout << "YES" << '\n';
    for (auto [f, s] : edges) {
        cout << f + 1 << ' ' 
            << s + 1 << '\n';
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}