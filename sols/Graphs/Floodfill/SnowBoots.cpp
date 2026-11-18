#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

void dfs(int node, int boot, int n, int b, vector<vector<bool>>& vis,
    vector<int>& ft, vector<pair<int, int>>& boots, bool bet) {
    if (node >= n - 1) {
        vis[n - 1][boot] = 1;
        return;
    }
    if (boot >= b || vis[node][boot] || (ft[node] 
        > boots[boot].f && !bet)) {
        return;
    }
    vis[node][boot] = 1;
    dfs(node, boot + 1, n, b, vis, ft, boots, false);
    dfs(node, boot + 1, n, b, vis, ft, boots, true);
    if (bet) return;
    int max = min(n - 1, node + boots[boot].s);
    for (int i = node + 1; i <= max; i++) {
        dfs(i, boot, n, b, vis, ft, boots, false);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);
    int n, b; cin >> n >> b;
    vector<int> ft(n);
    for (int& i : ft) cin >> i;
    vector<pair<int, int>> boots(b);
    for (auto& i : boots) {
        cin >> i.f >> i.s;
    }
    vector<vector<bool>> vis(n, vector<bool>(b));
    dfs(0, 0, n, b, vis, ft, boots, 0);
    for (int i = 0; i < b; i++) {
        if (vis[n - 1][i]) {
            cout << i << '\n';
            return 0;
        }
    }
}
/*
Algorithm:
Use a floodfill algorithm to fill in all the possible
"states" (tile n with boot b on).
*/