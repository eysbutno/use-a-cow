#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
bool isl[50][50], s[50][50], d[50][50];
int comp[50][50], dist[15][50][50],
    dp[1 << 15][15], n, m;
int dr[]{1, -1, 0, 0}, dc[]{0, 0, -1, 1};
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
bool valid(int r, int c) {
    return (r >= 0 && r < n &&
            c >= 0 && c < m &&
            !d[r][c]);
}
void ff(int r, int c, int col) {
    if (!valid(r, c) || !isl[r][c]
        || comp[r][c] == col) {
        return;
    }
    comp[r][c] = col;
    for (int i = 0; i < 4; i++) {
        ff(r + dr[i], c + dc[i], col);
    }
}
vector<vector<int>> calcDist(int cnt) {
    queue<array<int, 3>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (comp[i][j] != -1) {
                q.push({i, j, comp[i][j]});
                dist[comp[i][j]][i][j] = 0;
            }
        }
    }
    vector<vector<int>> res(cnt, vector<int>(cnt, INF));
    while (!q.empty()) {
        auto [r, c, id] = q.front(); q.pop();
        if (comp[r][c] != -1) {
            smin(res[id][comp[r][c]], dist[id][r][c]);
        }
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (valid(r1, c1) && smin(dist[id][r1][c1], 
                dist[id][r][c] + s[r1][c1])) {
                q.push({r1, c1, id});
            }
        }
    }
    return res;
}
int main() {
    freopen("island.in", "r", stdin);
    freopen("island.out", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            isl[i][j] = (c == 'X');
            s[i][j] = (c == 'S');
            d[i][j] = (c == '.');
            comp[i][j] = -1;
        }
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (isl[i][j] && comp[i][j] == -1) {
                ff(i, j, cur++);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < cur; k++) {
                dist[k][i][j] = INF;
            }
        }
    }
    auto dx = calcDist(cur);
    for (int i = 0; i < (1 << cur); i++) {
        for (int j = 0; j < cur; j++) {
            dp[i][j] = INF;
        }
    }
    for (int i = 0; i < cur; i++) {
        dp[1 << i][i] = 0;
    }
    for (int i = 0; i < (1 << cur); i++) {
        if (__builtin_popcount(i) < 2) continue;
        for (int j = 0; j < cur; j++) {
            if (!(i >> j & 1)) continue;
            for (int k = 0; k < cur; k++) {
                if (j == k || !(i >> k & 1)) continue;
                smin(dp[i][j], dp[i ^ (1 << j)][k] + dx[j][k]);
            }
        }
    }
    int res = INF;
    for (int i = 0; i < cur; i++) {
        smin(res, dp[(1 << cur) - 1][i]);
    }
    cout << res << '\n';
}
/**
 * TASK: Island Travels.
 * Basically, just Bitmask DP bash it.
 * You first floodfill each island, then
 * run some BFS to calculate the distances.
 * Then, bitmask DP bash it. BOOM!
*/