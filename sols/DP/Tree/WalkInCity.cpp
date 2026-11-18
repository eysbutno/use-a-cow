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
const int MOD = 998244353;
void solve() {
    int n; cin >> n;
    vector adj(n, vector<int>());
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    vector dp(n, vector(2, 0LL));
    /**
     * Case 1: In this subtree, there is 
     * one bad node of which the other bad
     * node has a bad ancestor.
     * 
     * Case 2: There are no such pairs, although
     * at least one node is colored.
    */
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
            // either previous, or color this root as bad.
            dp[u][0] += dp[v][0] + dp[v][1];
            // multiply out all the coefficients.
            dp[u][1] = (dp[u][1] + 1) * dp[v][1] + dp[u][1];
            // mod arithmetic stuff
            dp[u][0] %= MOD, dp[u][1] %= MOD;
        }
        ++dp[u][1], dp[u][1] %= MOD;
    }; dfs(0, -1, dfs);
    ll tot = 1;
    for (int i = 0; i < 2; i++) {
        tot += dp[0][i], tot %= MOD;
    }
    cout << tot << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: D. Sasha and a Walk in the City.
 * Case work the DP. (Cases are listed above)
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Monotonicity? Concavity? Anything else?
  * 4. Prove/justify any observations.
  * 5. If there are 1e9+7 edge cases and it's
  *    impossible to implement, maybe it's not right.
  * 6. For math formulas, try rewriting them.
  * 7. Break down the problem, or maybe reframe it.
  * 8. Loop through common techniques... binary search?
  *    DP? DFS/BFS/Graphs? 
  * 9. If your idea is almost certainly right, try some
  *    optimization techniques. Small to large merging?
  *    Deleting unnecessary stuff? Using a set? IDK.
*/