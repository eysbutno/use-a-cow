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
    int n, k; cin >> n >> k;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        adj[--p].push_back(i);
    }
    vector<int> s(n);
    for (int &i : s) {
        cin >> i;
    }
    vector<array<ll, 2>> dp(n);
    auto dfs = [&](int u, int t, auto&& dfs) -> void {
        dp[u][0] = 1LL * t * s[u];
        dp[u][1] = dp[u][0] + s[u];
        int z = sz(adj[u]);
        for (int v : adj[u]) {
            dfs(v, t / z, dfs);
        }
        sort(all(adj[u]), [&](int i, int j) {
            return (dp[i][1] - dp[i][0]) >
                   (dp[j][1] - dp[j][0]);
        });
        for (int v = 0; v < z; v++) {
            int ch = adj[u][v];
            dp[u][0] += dp[ch][v < (t % z)];
            dp[u][1] += dp[ch][v <= (t % z)];
        }
    }; dfs(0, k, dfs);
    cout << dp[0][0] << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * Paths on the Tree - Codeforces
 * We obviously need to split up the paths, such
 * that most paths receive sz_adj / sz_paths. Then,
 * we just need to figure out how to split up
 * the "extra" paths that we still have.
*/