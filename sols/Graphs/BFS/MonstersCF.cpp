#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int& i : a) cin >> i;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[--x].pb(--y);
        adj[y].pb(x);
    }
    vector<bool> vis(n);
    bool res = false;
    auto bfs = [&](int v) {
        set<int> seen;
        set<pii> cur = {{0, v}};
        while (!cur.empty()) {
            auto [t, u] = *begin(cur);
            cur.erase(begin(cur));
            if (t > sz(seen)) break;
            seen.insert(u), vis[u] = 1;
            for (int i : adj[u]) {
                if (!seen.count(i)) {
                    cur.insert({a[i], i});
                }           
            } 
        }
        return sz(seen) == n;
    };
    for (int i = 0; i < n; i++) {
        if (!a[i] && !vis[i]) {
            res = res | bfs(i);
        }
    }
    cout << (res ? "YES" : "NO") << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Monsters (CF).
 * Check each possible candidate vertice.
 * 
 * The criteria for a candidate vertice is as
 * follows:
 * 1. The vertice must have a[i] = 0.
 * 2. This vertice must not have been a vertice
 *    that can be reached from some other candidate.
*/