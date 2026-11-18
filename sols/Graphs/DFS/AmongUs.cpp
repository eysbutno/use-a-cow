#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

int dfs(int node, int& num, bool color, 
    bool& bad, vector<int>& col, vector<bool>& vis, 
    vector<vector<pair<int, int>>>& adj) {
    if (col[node] == (int) !color) {
        bad = 1; return 0;
    }
    if (vis[node] || bad) return 0;
    vis[node] = 1;
    col[node] = color;
    ++num;
    int cnt = color;
    for (auto i : adj[node]) {
        if (i.s) {
            cnt += dfs(i.f, num, color, 
                bad, col, vis, adj);
        } else {
            cnt += dfs(i.f, num, !color, 
                bad, col, vis, adj);
        }
    }
    return cnt;
}
void solve() {
    int n, q; cin >> n >> q;
    vector<vector<pair<int, int>>> adj(n + 1);
    while (q--) {
        int t, i, j; cin >> t >> i >> j; --t;
        adj[i].push_back({j, t});
        adj[j].push_back({i, t});
    }
    vector<bool> vis(n + 1);
    vector<int> col(n + 1, -1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            bool bad = 0;
            int num = 0;
            int ok = dfs(i, num, 0, 
                bad, col, vis, adj);
            if (bad) {
                cout << -1 << '\n';
                return;
            }
            ans += max(ok, num - ok);
        }
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
/*
If X accuses Y, then X and Y have to be
different colors. If X vouches Y, they have
to be the same color. If there is a conflict
where one astronaut should be both, then it's invalid.

To apply this approach, we just find the maximum # of
"imposter" colored astronauts per connected component and
add it up. For the precise logic, just read the solve() funct
*/