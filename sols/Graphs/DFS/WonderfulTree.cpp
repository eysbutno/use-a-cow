#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (ll &i : a) {
        cin >> i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        adj[--p].push_back(i);
    }
    ll res = 0;
    vector<ll> diff(n);
    const auto fix = [&](int u, auto &&self) -> void {
        // lazily update a[u] based on all the path updates.
        for (int v : adj[u]) {
            self(v, self);
            diff[u] += diff[v];
            diff[v] = 0;
        }
        a[u] += diff[u];
    };
    const auto dfs = [&](int u, auto &&self) -> void {
        // solves the problem for the subtree of u.
        ll sum = 0;
        for (int v : adj[u]) {
            self(v, self);
            sum += a[v];
        }
        if (a[u] <= sum) { return; }
        queue<array<int, 2>> q; // {node, dep}
        for (int v : adj[u]) {
            q.push({v, 1});
        }
        ll need = a[u] - sum;
        while (!q.empty() && need > 0) {
            auto [node, dep] = q.front(); q.pop();
            ll sub = 0;
            for (int nxt : adj[node]) {
                q.push({nxt, dep + 1});
                sub += a[nxt];
            }
            ll app = min(need, (adj[node].empty() ? ll(1e15) : sub) - a[node]);
            need -= app;
            res += app * dep;
            diff[node] += app;
        }
        for (int v : adj[u]) {
            fix(v, fix);
            diff[v] = 0;
        }
    };
    dfs(0, dfs);
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * Note that by the property, you will end up
 * adding some number to entire paths, mainly if
 * they are "at the max". At every depth, consider
 * how much more we can add to this part without
 * updating the children. This way, we are being efficient.
 */