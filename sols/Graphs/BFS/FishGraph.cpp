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
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<array<int, 2>> edges;
    auto hasPath = [&](int st, int fin) -> bool {
        // returns: if there's a simple path from u -> fin
        // (of course, ignoring the edge from u -> fin)
        vector<int> par(n, -1);
        par[st] = fin;
        queue<int> bfs({st});
        while (sz(bfs) && par[fin] == -1) {
            int u = bfs.front(); bfs.pop();
            for (int v : adj[u]) {
                if (par[v] == -1 && !(u == st && v == fin)) {
                    par[v] = u, bfs.push(v);
                }
            }
        }
        if (par[fin] == -1) return false;
        int ptr = fin;
        do {
            int nxt = par[ptr];
            edges.push_back({nxt, ptr});
            ptr = nxt;
        } while (ptr != fin);
        int cnt = 2;
        for (int u : adj[fin]) {
            if (u != st && u != par[fin]) {
                edges.push_back({fin, u});
                --cnt;
            }
            if (!cnt) break;
        }
        return true;
    };
    for (int i = 0; i < n; i++) {
        if (sz(adj[i]) < 4) continue;
        if (sz(edges)) break;
        for (int v : adj[i]) {
            if (hasPath(v, i)) {
                break;
            }
        }
    }
    if (!edges.empty()) {
        cout << "YES" << "\n";
        cout << sz(edges) << "\n";
        for (auto [u, v] : edges) {
            cout << u + 1 << " " << v + 1 << "\n";
        }
    } else {
        cout << "NO" << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * B. Fish Graph (CF Round 869)
 * First, brute force on each node in the graph. Ignore
 * any nodes that have a degree less than 4.
 * Claim: If there exists ONE cycle involving this current node u,
 * there exists a fish graph.
 * Proof: Let the 4 other connections be {a, b, c, d}. Observe that we
 * can simply involve two of these connections (e.g. {a, b}) for the cycle.
 * Then, we can use {c, d} as our extra edges.
*/