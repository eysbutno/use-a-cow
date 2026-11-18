#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n, m; 
    cin >> n >> m;
    vector<set<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        if (u > v) swap(u, v);
        adj[--u].insert(--v);
    }
    ll res = 0;
    auto merge = [&](int i, int j) -> void {
        if (sz(adj[i]) < sz(adj[j])) {
            swap(adj[i], adj[j]);
        }
        for (int v : adj[j]) {
            adj[i].insert(v);
        }
        adj[j].clear();
    };
    for (int i = 0; i < n; i++) {
        res += sz(adj[i]);
        if (!sz(adj[i])) continue;
        int low = *begin(adj[i]);
        adj[i].erase(low);
        merge(low, i);
    }
    cout << res - m << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Making Friends (USACO Plat)
 * Directly uniting friends takes too much time.
 * Observe that we only need to link the smallest indexed
 * friend to all the other friends every single time. Thus,
 * we can small-to-large merge to get a fast solution.
*/