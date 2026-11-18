#include <bits/stdc++.h>
using namespace std;

const int MAX = 101;
bool vis[MAX][MAX];
struct State {
    int p1, p2, ops;
};
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);
    int x, y, k, m; cin >> x >> y >> k >> m;
    queue<State> q; q.push({0, 0, 0});
    vis[0][0] = 1; int ans = 2e9;
    while (!q.empty()) {
        State p = q.front(); q.pop(); 
        int px = p.p1, py = p.p2, pd = p.ops + 1;
        int t1 = min(px, y - py), t2 = min(py, x - px);
        int dx[] = {x, px, px, 0, px - t1, px + t2};
        int dy[] = {py, y, 0, py, py + t1, py - t2};
        for (int i = 0; i < 6; i++) {
            if (!vis[dx[i]][dy[i]] && pd <= k) {
                q.push({dx[i], dy[i], pd});
                vis[dx[i]][dy[i]] = 1;
            }
        }
        ans = min(ans, abs(px + py - m));
    }
    cout << ans << "\n";
    return 0;
}