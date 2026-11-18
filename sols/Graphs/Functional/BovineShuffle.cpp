#include <bits/stdc++.h>
using namespace std;

vector<int> vis, cycle, trav;
void dfs(int node) {
    vis[node] = 1;
    int next = trav[node];
    if (vis[next] == 1) cycle.push_back(next);
    if (!vis[next]) dfs(next);
    vis[node] = 2;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);
    int n; cin >> n;
    vis.resize(n), trav.resize(n);
    for (int &i : trav) {
        cin >> i; i--;
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }
    int ans = cycle.size();
    for (int i : cycle) {
        int cur = trav[i];
        while (cur != i) {
            ans++; cur = trav[cur];
        }
    }
    cout << ans << "\n";
    return 0;
}
/*
Type: DFS, Cycles
Algorithm:
"Color" each cow by running DFS
For each color/group, run Floyd's algorithm
to the # of cows in a cycle
Nice trick used:
Mark each node 0 for not visited,
1 for processing, and 2 for complete
The reason this is necessary is because if a node is visited but it's already processed,
then it can't be part of a cycle (otherwise it'd be double counted)
*/