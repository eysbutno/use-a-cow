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
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<ll> a(n);
    for (ll &i : a) {
        cin >> i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    vector<ll> dp(n);
    auto join = [&](ll a, ll b) -> ll {
        return max(a, b) + sqrtl(min(a, b));
    };  
    auto dfs1 = [&](int u, int p, auto&& dfs1) -> void {
        dp[u] = a[u]; // bare minimum.
        for (int v : adj[u]) if (v != p) {
            dfs1(v, u, dfs1);
            smax(dp[u], join(a[u], dp[v]));
        }
    }; dfs1(0, -1, dfs1);
    auto dfs2 = [&](int u, int p, ll top, 
                    auto&& dfs2) -> void {
        ll l1 = join(a[u], top), l2 = a[u];
        for (int v : adj[u]) if (v != p) {
            ll cost = join(a[u], dp[v]);
            if (cost > l1) {
                swap(l1, l2), l1 = cost;
            } else if (cost > l2) {
                l2 = cost;
            }
        }
        for (int v : adj[u]) if (v != p) {
            if (l1 == join(a[u], dp[v])) {
                // cannot use this path, switch.
                smax(dp[v], join(a[v], l2));
                dfs2(v, u, l2, dfs2);
            } else {
                smax(dp[v], join(a[v], l1));
                dfs2(v, u, l1, dfs2);
            }
        }
    }; dfs2(0, -1, 0, dfs2);
    cout << *max_element(all(dp)) << "\n";
}
/**
 * TASK: Jovial Jaunt (BAPC).
 * Reroot bash. Combine in O(1). FML
 * for not getting this in contest!!!.
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