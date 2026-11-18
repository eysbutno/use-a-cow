#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MOD = 1e9 + 7,
    MAX = 1e5 + 1;
vector<int> adj[MAX];
ll dp[MAX][2];
void dfs(int node, int prev) {
    dp[node][0] = 1;
    dp[node][1] = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            dp[node][0] *= (dp[i][0] 
                + dp[i][1]);
            dp[node][1] *= dp[i][0];
            dp[node][0] %= MOD;
            dp[node][1] %= MOD;
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    dfs(1, -1);
    cout << ((dp[1][0] + dp[1][1]) % MOD);
}
/*
Use DP to solve subtrees and
eventually get your final answer.

If the parent node is white, the
# of possible colorings is all the 
possibilities from each subtree
(black + white colorings) multiplied by
each other. If the parent node is black,
it's all the white colorings multiplied
by each other.
*/