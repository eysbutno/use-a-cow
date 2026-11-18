#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7,
    MAX = 1e5 + 1;
vector<int> adj[MAX];
ll dp[MAX][4];
int colored[MAX];
void dfs(int node, int prev) {
    for (int i = 1; i <= 3; i++) {
        if (!colored[node] || 
            colored[node] == i) {
            dp[node][i] = 1;
        }
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            dp[node][1] *= (dp[i][2] 
                + dp[i][3]);
            dp[node][2] *= (dp[i][1] 
                + dp[i][3]);
            dp[node][3] *= (dp[i][1]
                + dp[i][2]);
            for (int j = 1; j <= 3; j++) {
                dp[node][j] %= MOD;
            }
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("barnpainting.in", "r", stdin);
    freopen("barnpainting.out", "w", stdout);
    int n, k; cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    for (int i = 0; i < k; i++) {
        int b, c; cin >> b >> c;
        colored[b] = c;
    }
    dfs(1, -1);
    ll res = dp[1][1] + 
        dp[1][2] + dp[1][3];
    cout << res % MOD << '\n';
}
/*
Solve each subtree to get your 
final answer. Too lazy to explain
the math but it's pretty simple.
*/