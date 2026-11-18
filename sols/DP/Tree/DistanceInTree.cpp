#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define f first 
#define s second 
    
const int MAX = 5e4 + 1;
vector<int> adj[MAX];
ll n, k, dp[MAX][501];
void dfs(int node, int prev) {
    dp[node][0] = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
        }
    }
    for (int i = 0; i < k; i++) {
        dp[prev][i + 1] += dp[node][i];
    }
}
void dfs2(int node, int prev) {
    if (node != 1) {
        for (int i = k; i >= 2; i--) {
            dp[node][i] += dp[prev][i - 1]
                        - dp[node][i - 2];
        }
        dp[node][1]++;
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dfs2(i, node);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs(1, 0);
    dfs2(1, 0);
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        sum += dp[i][k];
    }
    cout << sum / 2 << '\n';
}
/*
For each node, first find dp[i][j] 
for that node's subtree, where dp[i][j]
is the # of nodes j edges away from node i.

Next, run DFS again. You can find the global
value of dp[i][j] to be this:
dp[i][j] = (dp[i][j] for subtree)
    + dp[prev][j - 1] - dp[i][j - 2].
*/