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

const ll LINF = -1e18;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    vector<ll> dp(n, LINF);
    ll res = 0;
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        vector<ll> s(4, LINF);
        s[0] = 0; // 0 for 0 indeg
        for (int i : adj[u]) {
            if (i == p) continue;
            dfs(i, u, dfs);
            for (int j = 3; j >= 0; j--) {
                int idx = min(j + 1, 3);
                smax(s[idx], s[j] + dp[i]);
            }
        }
        dp[u] = LINF;
        for (int i = 0; i < 4; i++) {
            smax(dp[u], s[i] + (i != 1 ? a[u] : 0));
            smax(res, s[i] + (i != 2 ? a[u] : 0));
        }
    };  
    dfs(0, -1, dfs);
    cout << res << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Compressed Tree (CF).
 * Use tree DP to calculate answer.
 * Main idea is that for each node,
 * either we take it's node's subtree
 * as the compressed node, or we connect
 * it to an ancestor.
*/