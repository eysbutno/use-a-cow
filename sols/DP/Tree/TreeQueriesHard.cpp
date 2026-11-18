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
    if (n == 1) {
        cout << "0\n";
        return;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    vector<int> dp(n), occ(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
            occ[u] += (dp[v] == 0);
            dp[u] += dp[v];
        }
        dp[u] += max(0, occ[u] - 1);
    }; dfs(0, -1, dfs);
    auto dfs2 = [&](int u, int p, auto&& dfs2) -> void {
        for (int v : adj[u]) if (v != p) {
            int dx = dp[u] - max(0, occ[u] - 1) - dp[v],
                dc = occ[u] - (dp[v] == 0);
            dx += max(0, dc - 1);
            dp[v] += dx - max(0, occ[v] - 1);
            occ[v] += (dx == 0);
            dp[v] += max(0, occ[v] - 1);
            dfs2(v, u, dfs2);
        }
    }; dfs2(0, -1, dfs2);
    cout << *min_element(all(dp)) + 1 << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: D2. Tree Queries (Hard)
 * Solve the problem greedily for one
 * root, and use rerooting to solve it
 * for all other roots.
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * Brute force (or set some) restrictions, to
  * simplify the problem.
  * Actually do something and don't just stare at
  * the screen....!
*/
/*
const int MOD = 1e9 + 7;
template<class T> void add(T& a, T b) {
	a += b, a %= MOD;
}
template<class T> void sub(T& a, T b) {
	a > b ? a -= b : a -= b, a += MOD;
}
template<class T> void mul(T& a, T b) {
	a = (a * b) % MOD;
}
*/