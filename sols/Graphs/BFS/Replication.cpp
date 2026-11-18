#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e3;
const int INF = 1e9;
char grid[N][N];
bool vis[N][N];
int rdist[N][N], cst[N][N], n, d;
int dr[]{1, -1, 0, 0}, dc[]{0, 0, 1, -1};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> d;
    queue<pii> rk;
    queue<pair<int, pii>> st;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            rdist[i][j] = INF;
            cst[i][j] = -INF;
            if (grid[i][j] == '#') {
                rdist[i][j] = 0;
                rk.push({i, j});
            } else if (grid[i][j] == 'S') {
                st.push({0, {i, j}});
                vis[i][j] = true;
            }
        }
    }
    auto valid = [&](int r, int c) {
        return (r >= 0 && r < n &&
                c >= 0 && c < n &&
                grid[r][c] != '#');
    };
    while (!rk.empty()) {
        auto [r, c] = rk.front(); rk.pop();
        int dx = rdist[r][c];
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (valid(r1, c1) && dx + 1 < rdist[r1][c1]) {
                rdist[r1][c1] = dx + 1;
                rk.push({r1, c1});
            }
        }
    }
    priority_queue<pair<int, pii>> pq;
    while (!st.empty()) {
        auto N = st.front(); st.pop();
        int t = N.f, r = N.s.f, c = N.s.s;
        pq.push({rdist[r][c] - 1, {r, c}});
        cst[r][c] = rdist[r][c] - 1; 
        if (t / d == rdist[r][c]) {
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (valid(r1, c1) && !vis[r1][c1] &&
                t + 1 <= (ll) d * rdist[r1][c1]) {
                vis[r1][c1] = true;
                st.push({t + 1, {r1, c1}});
            }
        }
    }
    while (!pq.empty()) {
        auto N = pq.top(); pq.pop();
        int t = N.f, r = N.s.f, c = N.s.s;
        if (t == 0 || cst[r][c] != t) continue;
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (r1 >= 0 && r1 < n && 
                c1 >= 0 && c1 < n &&
                grid[r1][c1] != '#' &&
                t - 1 > cst[r1][c1]) {
                vis[r1][c1] = true;
                cst[r1][c1] = t - 1;
                pq.push({t - 1, {r1, c1}});
            }
        }
    }
    int res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res += cst[i][j] >= 0;
        }
    }
    cout << res << '\n';
}
/**
 * TASK: Replication.
 * Figure out all the cells that can hold
 * a robot that will expand properly into
 * a "diamond" shape. Then use a Dijkstras-like
 * algorithm to find all the possible cells.
 * 
 * NOTE: To check if a cell can be a center:
 * Use BFS, and check the following conditions:
 * T / D > rock_distance[r][c]:
 * If this isn't fulfilled, then stop propogating
 * from this cell.
 * T + 1 <= d * rock_distance[r][c].
 * If this isn't fulfilled, you cannot propogate
 * to a cell (r, c).
*/