#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

void solve() {
    int n, r, q;
    cin >> n >> r >> q;
    vector<int> reg(n);
    cin >> reg[0], --reg[0];
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p, h; cin >> p >> h;
        adj[--p].push_back(i);
        reg[i] = --h;
    }
    const int b = sqrt(n);
    vector<int> tin(n), tout(n), mp(n);
    vector<vector<int>> comp(r);
    int timer = 0;
    auto tour = [&](int u, auto&& tour) -> void {
        tin[u] = timer++, mp[tin[u]] = u;
        comp[reg[u]].push_back(tin[u]);
        for (int v : adj[u]) {
            tour(v, tour);
        }
        tout[u] = timer;
    }; tour(0, tour);
    vector<vector<int>> calc;
    vector<int> id(r, -1);
    auto dfs = [&](int u, int e1, int tot,
                   auto&& dfs) -> void {
        if (reg[u] == e1) ++tot;
        calc[id[e1]][reg[u]] += tot;
        for (int v : adj[u]) {
            dfs(v, e1, tot, dfs);
        }
    };
    int run = 0;
    for (int i = 0; i < r; i++) {
        if (sz(comp[i]) >= b) {
            id[i] = run++;
            calc.push_back(vector<int>(r));
            dfs(0, i, 0, dfs);
        }
    }
    while (q--) {
        int e1, e2;
        cin >> e1 >> e2;
        --e1, --e2;
        if (sz(comp[e1]) >= b) {
            cout << calc[id[e1]][e2] << "\n";
        } else {
            int tot = 0;
            for (int u : comp[e1]) {
                tot += lower_bound(all(comp[e2]), tout[mp[u]])
                     - lower_bound(all(comp[e2]), tin[mp[u]]);
            }
            cout << tot << "\n";
        }
    }
}
int main() {
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Regions (IOI)
 * The idea: for regions with size > sqrt(N), precompute
 * the result. Otherwise, answer the queries online.
 * 
 * For the precomputed queries: Let e1 be the "ancestor" region.
 * At every node, store the # of occurences e1 that you have seen so far.
 * Treat every node as if it was the "child" region. Then, at every
 * node, add the # of e1 occurences to your result.
 * 
 * For the queries answered online: Euler tour, then binary search.
*/