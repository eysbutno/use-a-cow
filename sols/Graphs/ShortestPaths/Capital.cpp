#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first
#define s second

const int INF = 1e9;
const int MAX = 2e5 + 1;
vector<int> adj[MAX];
int dp[MAX][2];
bool vis[MAX];
void dfs(int node) {
    vis[node] = true;
    dp[node][1] = dp[node][0];
    for (int i : adj[node]) {
        if (dp[i][0] > dp[node][0] 
            && !vis[i]) {
            dfs(i);
        }
        if (dp[i][0] > dp[node][0]) {
            dp[node][1] = min(
                dp[node][1], dp[i][1]
            );
        } else {
            dp[node][1] = min(
                dp[node][1], dp[i][0]
            );
        }
    }
}
void solve() {
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = INF;
        dp[i][1] = INF;
        adj[i].clear();
        vis[i] = false;
    }
    for (int i = 0; i < m; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
    }
    queue<int> q;
    q.push(1);
    dp[1][0] = 0;
    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (int i : adj[p]) {
            if (dp[p][0] + 1 < dp[i][0]) {
                dp[i][0] = dp[p][0] + 1;
                q.push(i);
            }
        }
    }
    dfs(1);
    for (int i = 1; i <= n; i++) {
        cout << dp[i][1] << ' ';
    }
    cout << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Run DFS. When choosing when to run
 * DFS, make sure it's strictly going
 * from lower to higher distances.
 * 
 * Note: Being a bit more selective
 * with your DFS takes care of undirected
 * edges, and other conflicts.
*/