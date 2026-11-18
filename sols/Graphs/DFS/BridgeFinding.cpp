#include <bits/stdc++.h>
using namespace std;
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
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[1] = 1; dfs(1);
    cout << cnt << '\n';
}
/*
Uses the DFS tree
to find the # of
bridges in a graph.

To count # of bridges,
we define a DP array.
dp[i] = (edges going
up from i) - (edges
going down from i)
+ dp[v], if v is a
child of node i.
If dp[i] = 0 and
i is not the root,
then there's a bridge.
If you do some thinking,
the only way dp[i] = 0
is if there are no back
edges going up from node i's
sub-spanning-tree.s
*/