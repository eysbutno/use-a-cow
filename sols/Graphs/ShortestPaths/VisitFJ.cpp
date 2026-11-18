#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

const int MAX = 101;
int grid[MAX][MAX], dist[MAX][MAX];
int dr[] = {1, 0, -1, 0, 3, 0, -3, 0, 
    2, 2, 1, 1, -1, -1, -2, -2};
int dc[] = {0, 1, 0, -1, 0, 3, 0, -3, 
    1, -1, 2, -2, 2, -2, 1, -1};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);
    int n, T; cin >> n >> T;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            dist[i][j] = 2e9;
        }
    }
    auto check = [&](int r, int c) {
        return (r >= 0 && r < n &&
            c >= 0 && c < n);
    };
    dist[0][0] = 0;
    priority_queue<pair<int, pii>> q;
    q.push({0, {0, 0}});
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        int r = p.s.f, c = p.s.s, t = -p.f;
        if (dist[r][c] != t) continue;
        for (int i = 0; i < 16; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (check(r1, c1) && dist[r][c] + 3 * T
                + grid[r1][c1] < dist[r1][c1]) {
                dist[r1][c1] = dist[r][c] + 
                    3 * T + grid[r1][c1];
                q.push({-dist[r1][c1], {r1, c1}});
            }
        }
        int mDist = 2 * (n - 1) - r - c;
        if (mDist < 3) {
            dist[n - 1][n - 1] = min(
                dist[n - 1][n - 1],
                dist[r][c] + mDist * T
            );
        }
    }
    cout << dist[n - 1][n - 1];
}
/*
NGL my previous solution
idea was like, really dumb.

Observation 1: we can Dijkstra
it. 
Observation 2: the paths in between
literally don't matter.
Observation 3: just have an edge
between every node that can
be visited by moving 3 times.

Boom, and it works.
*/