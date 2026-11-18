#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 1;
vector<int> adj[MAX];
int dp[MAX][2];
void dfs(int node, int prev) {
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            dp[node][0] += max(
                dp[i][0], dp[i][1]
            );
        }
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dp[node][1] = max(dp[node][1], 
                dp[node][0] + dp[i][0] + 1
                - max(dp[i][0], dp[i][1])
            );
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(1, -1);
    cout << max(dp[1][1], dp[1][0]);
}