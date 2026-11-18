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
constexpr int MOD = 1e9 + 7;
void solve() {
    int n; cin >> n;
    vector<int> val(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
        if (val[i] < 0) {
            val[i] += MOD;
        }
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<ll> dp(n), occ(n);
    auto dfs1 = [&](int u, int p, 
                    auto&& dfs1) -> void {
        dp[u] = val[u], occ[u] = 1;
        for (int v : adj[u]) if (v != p) {
            dfs1(v, u, dfs1);
            dp[u] -= dp[v]; // alternating
            dp[u] += 1LL * val[u] * occ[v];
            dp[u] = (dp[u] % MOD) + MOD * (dp[u] < 0);
            occ[u] += occ[v];
        }
    }; dfs1(0, -1, dfs1);
    ll res = 0;
    auto dfs2 = [&](int u, int p, ll top,
                    auto&& dfs2) -> void {
        top = 1LL * val[u] * (n - occ[u]) - top;
        top = (top % MOD) + (top < 0) * MOD;
        res += top + dp[u], res %= MOD;
        for (int v : adj[u]) if (v != p) {
            ll nt = top + dp[u] + dp[v] - val[u] * occ[v];
            nt = (nt % MOD) + (nt < 0) * MOD;
            dfs2(v, u, nt, dfs2);
        }
    }; dfs2(0, -1, 0, dfs2);
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Alternating Tree (CF)
 * Do some rerooting DP. Let each root be
 * the start of some path.
*/