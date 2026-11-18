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
    int n; cin >> n;
    string s; cin >> s;
    vector adj(n, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector dp(n, vector(n, 0));
    vector nxt(n, vector(n, -1));
    vector comps(n, vector<array<int, 2>>());
    // precalc "next" values on path
    int fst = -1; // current start
    auto dfs = [&](int u, int p, int dx, 
                   auto&& dfs) -> void {
        if (u != fst) {
            if (p == fst) {
                nxt[fst][u] = u;
            } else {
                nxt[fst][u] = nxt[fst][p];
            }
        }
        comps[dx].push_back({fst, u});
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, dx + 1, dfs);
        }
    };
    for (int i = 0; i < n; i++) {
        fst = i, dfs(i, -1, 0, dfs);
    }
    // precalc path lengths of 1 and 2.
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
        for (int j : adj[i]) {
            dp[i][j] = 1 + (s[i] == s[j]);
        }
    }
    // calculate the other path lengths.
    for (int i = 2; i < n; i++) {
        for (auto [u, v] : comps[i]) {
            int nt = nxt[u][v], pv = nxt[v][u];
            dp[u][v] = max({dp[nt][pv] + 2 * (s[u] == s[v]), 
                            dp[u][pv], dp[nt][v]});
            smax(dp[v][u], dp[u][v]);
        }
    }
    int res = -1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            smax(res, dp[i][j]);
        }
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Sub-Palindromic Tree
 * Problem Statement:
 * Find the maximum palindromic subsequence
 * that is formed by a path on the tree.
 * 
 * Note that for each subsequence, we can
 * view it as adding two at a time for each
 * endpoint. This motivates a DP solution.
 * Let dp[u][v] be the max subsequence on the
 * path from u to v.
 * 
 * Now, ignoring the order that we process
 * the DP states, the transition should now be:
 * dp[u][v] = dp[next(u)][prev(v)] + 2 * (s[u] == s[v]).
 * However, we still have the option to exclude one endpoint.
 * So, also consider dp[next(u)][v] and dp[u][prev(v)].
 * 
 * Now, for the order. Like in range DP, you just compute the path
 * lengths in ascending order of length.
*/