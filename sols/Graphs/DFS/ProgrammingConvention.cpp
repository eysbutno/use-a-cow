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

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        adj[--p].pb(i);
    }
    vector<int> sub(n);
    auto init = [&](int u, auto&& init) -> void {
        sub[u] = 1;
        for (int i : adj[u]) {
            init(i, init), sub[u] += sub[i];
        }
    };
    init(0, init);
    auto dfs = [&](int u, int k, auto&& dfs) -> int {
        int mx = -1, ind = -1;
        for (int i : adj[u]) {
            if (smax(mx, sub[i])) {
                ind = i;
            }
        }
        int tot = sub[u] - 1;
        if (!tot) return 0;
        if (mx - k <= tot - mx) {
            return (tot - k) / 2;
        }
        int add = tot - mx;
        return add + dfs(ind, max(0, k + add - 1), dfs);
    };
    cout << dfs(0, 0, dfs) << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Main idea is that at every node, 
 * you want to pair up as many other
 * nodes from different children as
 * possible.
*/