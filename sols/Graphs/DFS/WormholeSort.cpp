#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e5 + 1;
int n, m, locs[MAX], a[MAX], b[MAX], w[MAX];
void dfs(int node, int col, vector<vector<int>>& adj,
    vector<int>& vis, vector<int>& color) {
    vis[node] = 1, color[node] = col;
    for (int i : adj[node]) {
        if (!vis[i]) dfs(i, col, adj, vis, color);
    }
}
bool check(int size) {
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= m; i++) {
        if (w[i] >= size) {
            adj[a[i]].push_back(b[i]);
            adj[b[i]].push_back(a[i]);
        }
    }
    vector<int> vis(n + 1), color(n + 1);
    int col = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) dfs(i, ++col, adj, vis, color);
    }
    for (int i = 1; i <= n; i++) {
        if (color[locs[i]] != color[i]) {
            return false;
        }
    }
    return true;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("wormsort.in", "r", stdin);
    freopen("wormsort.out", "w", stdout);
    cin >> n >> m;
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        cin >> locs[i];
        if (locs[i] != i) {
            flag = true;
        }
    }
    int sizes[m];
    for (int i = 1; i <= m; i++) {
        cin >> a[i] >> b[i] >> w[i];
        sizes[i - 1] = w[i];
    }
    if (!flag) {
        cout << -1 << "\n";
        return 0;
    }
    sort(sizes, sizes + m);
    int low = 0, high = m - 1; // idx
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(sizes[mid])) low = mid;
        else high = mid - 1;
    }
    cout << sizes[low] << "\n";
}