#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 3e5 + 1;
vector<int> adj[MAX];
int depth[MAX], dp[MAX],
    cnt = 0;
void dfs(int node) {
    dp[node] = 0;
    for (int i : adj[node]) {
        if (!depth[i]) {
            depth[i] = depth[node] + 1;
            dfs(i); dp[node] += dp[i];
        } else if (depth[i] < depth[node]) {
            dp[node]++;
        } else if (depth[i] > depth[node]) {
            dp[node]--;
        }
    }
    dp[node]--;
    if (depth[node] != 1 
        && !dp[node]) {
        ++cnt;
    }
}
bool vis[MAX];
void span(int node, int prev) {
    vis[node] = true;
    for (int i : adj[node]) {
        if (!vis[i]) {
            cout << node << ' ' << i << '\n';
            span(i, node);
        } else if (i != prev && 
            depth[node] > depth[i]) {
            cout << node << ' ' << i << '\n';
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[1] = 1; dfs(1);
    if (cnt > 0) {
        cout << 0 << '\n';
        return 0;
    }
    span(1, -1);
}
/**
 * TASK: Bertown Roads.
 * Observation 1: If the graph
 * contains a bridge, it's impossible.
 * Observation 2: Your task is to
 * direct the graph so the whole graph
 * is strongly connected.
 * 
 * Use the DFS tree. Direct all spanning 
 * tree edges downwards, and back edges
 * upwards.
*/