#include <bits/stdc++.h>
using namespace std;

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int INF = 1e9;
int vis[20][20][20][20][4][4],
    dr[]{-1, 0, 1, 0}, 
    dc[]{0, 1, 0, -1};
char grid[20][20];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("cownav.in", "r", stdin);
    freopen("cownav.out", "w", stdout);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    vis[n - 1][0][n - 1][0][0][1] = 1;
    // distance is tracked in BFS states
    queue<vector<int>> q;
    q.push({n - 1, 0, n - 1, 0, 0, 1, 0});
    while (!q.empty()) {
        auto v = q.front(); q.pop();
        // v[0] = r1, v[1] = c1, v[2] = r2, v[3] = c2,
        // v[4] = d1, v[5] = d2, v[6] = distance
        auto end = [&](int r, int c) {
            return (r == 0 && c == n - 1);
        };
        if (end(v[0], v[1]) && end(v[2], v[3])) {
            cout << v[6] << '\n';
            return 0;
        }
        v[6]++;
        // rotate everything
        int d1 = (v[4] + 1) % 4, d2 = (v[5] + 1) % 4;
        if (smax(vis[v[0]][v[1]][v[2]][v[3]][d1][d2], 1)) {
            q.push({v[0], v[1], v[2], v[3], d1, d2, v[6]});
        }
        d1 = (d1 + 2) % 4, d2 = (d2 + 2) % 4;
        if (smax(vis[v[0]][v[1]][v[2]][v[3]][d1][d2], 1)) {
            q.push({v[0], v[1], v[2], v[3], d1, d2, v[6]});
        }
        // move forward
        auto canMove = [&](int r, int c, int d) {
            int r1 = r + dr[d], c1 = c + dc[d];
            return (r1 >= 0 && r1 < n && 
                    c1 >= 0 && c1 < n &&
                    !end(r, c) && grid[r1][c1] != 'H');
        };
        if (canMove(v[0], v[1], v[4])) {
            v[0] += dr[v[4]], v[1] += dc[v[4]];
        }
        if (canMove(v[2], v[3], v[5])) {
            v[2] += dr[v[5]], v[3] += dc[v[5]];
        }
        if (smax(vis[v[0]][v[1]][v[2]][v[3]][v[4]][v[5]], 1)) {
            q.push(v);
        }
    }
    cout << -1 << '\n';
}
/**
 * TASK: Cow Navigation.
 * Imagine there are two cows: Bessie if she started facing 
 * towards (1, 2), and Bessie if she faced (2, 1). Then,
 * you can maintain the following state: 
 * dist[r1][c1][r2][c2][d1][d2] = distance if cow 1 is at 
 * (r1, c1) with direction d1, and cow 2 is at (r2, c2) with 
 * direction d2.
*/