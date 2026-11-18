#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

const int MAX = 3e5 + 1;
vector<int> adj[MAX],
    adj2[MAX];
int depth[MAX], dp[MAX],
    leaf, dis = -1;
bool vis[MAX];
vector<pair<int, int>> bridges;
struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
} dsu(MAX);
void dfs(int node, int prev) {
    dp[node] = 0;
    for (int i : adj[node]) {
        if (depth[i] == 0) {
            depth[i] = depth[node] + 1;
            dfs(i, node); dp[node] += dp[i];
        } else if (depth[i] < depth[node]) {
            dp[node]++;
        } else if (depth[i] > depth[node]) {
            dp[node]--;
        }
    }
    dp[node]--;
    if (depth[node] != 1 
        && !dp[node]) {
        bridges.push_back({node, prev});
    } else if (prev != -1) {
        dsu.unite(node, prev);
    }
}
void dfs2(int node, int prev, int dist) {
    if (dis < dist) {
        dis = dist, leaf = node;
    }
    vis[node] = true;
    for (int i : adj2[node]) {
        if (i != prev) {
            dfs2(i, node, dist + 1);
        }
    }
}
int diameter() {
    int st = -1;
    for (auto& i : bridges) {
        int x = dsu.get(i.f),
            y = dsu.get(i.s);
        adj2[x].push_back(y);
        adj2[y].push_back(x);
        st = x; // arbitrary
    }
    dfs2(st, -1, 0);
    dis = 0;
    dfs2(leaf, -1, 0);
    return dis;
}
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    depth[1] = 1; dfs(1, -1);
    cout << diameter() << '\n';
}
/*

*/