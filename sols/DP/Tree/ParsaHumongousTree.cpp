#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#define pb push_back 

const int N = 1e5;
vector<int> adj[N];
ll l[N], r[N], dp[2][N];
void dfs(int node, int prev) {
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            ll r1 = dp[0][i],
                r2 = dp[1][i];
            dp[0][node] += max(
                r1 + abs(l[node] - l[i]),
                r2 + abs(l[node] - r[i])
            );
            dp[1][node] += max(
                r1 + abs(r[node] - l[i]),
                r2 + abs(r[node] - r[i])
            );
        }
    }
}
void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        adj[i].clear();
        dp[0][i] = 0;
        dp[1][i] = 0;
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1, 0);
    cout << max(dp[0][1], 
        dp[1][1]) << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Use a greedy stategy. For
 * each node, either set it
 * to a maximum or a minimum 
 * value. Use dp to do it.
*/