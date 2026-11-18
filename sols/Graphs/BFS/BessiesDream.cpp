#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct State {
    int r, c, s, d;
};
const int N = 1e3;
const int INF = 1e9;
int dp[N][N][2][4], 
    grid[N][N];
int dr[]{1, -1, 0, 0},
    dc[]{0, 0, 1, -1};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("dream.in", "r", stdin);
    freopen("dream.out", "w", stdout);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            for (int k = 0; k < 2; k++) {
                for (int l = 0; l < 4; l++) {
                    dp[i][j][k][l] = INF;
                }
            }
        }
    }
    dp[0][0][0][0] = 0;
    queue<State> q;
    q.push({0, 0, 0, 0});
    auto valid = [&](int r, int c) {
        return (r >= 0 && r < n &&
                c >= 0 && c < m &&
                grid[r][c] != 0);
    };
    while (!q.empty()) {
        auto [r, c, s, d] = q.front(); q.pop();
        int prev = dp[r][c][s][d], sPrev = s;
        auto blueCheck = [&](int r1, int c1) {
            if (grid[r1][c1] == 3) {
                return (bool) sPrev;
            }
            return true;
        };
        if (grid[r][c] == 2) {
            s = 1;
        }
        if (grid[r][c] == 4) {
            int r1 = r + dr[d],
                c1 = c + dc[d];
            s = 0;
            if (prev + 1 < dp[r1][c1][s][d] &&
                valid(r1, c1) && blueCheck(r1, c1)) {
                dp[r1][c1][s][d] = prev + 1;
                q.push({r1, c1, s, d});
                continue;
            }
        }
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i],
                c1 = c + dc[i];
            if (valid(r1, c1) && blueCheck(r1, c1)
                && prev + 1 < dp[r1][c1][s][i]) {
                dp[r1][c1][s][i] = prev + 1;
                q.push({r1, c1, s, i});
            }
        }
    }
    int res = INF;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 4; j++) {
            ckmin(res, dp[n - 1][m - 1][i][j]);
        }
    }
    cout << (res != INF ? res : -1);
}
/**
 * TASK: Bessie's Dream.
 * Use BFS. Maintain the 
 * following dist/dp states:
 * dp[r][c][s][d] is the minimum
 * distance to get to (r, c),
 * if s marks the status of smell,
 * and d is the direction.
*/