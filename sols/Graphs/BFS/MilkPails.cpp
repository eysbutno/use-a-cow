#include <bits/stdc++.h>
using namespace std;

const int inf = 2e9;
int dist[101][101];
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);
    int x, y, k, m; cin >> x >> y >> k >> m;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            dist[i][j] = inf;
        }
    }
    dist[0][0] = 0;
    queue<pair<int, int>> bfs; bfs.push({0, 0});
    while (!bfs.empty()) {
        auto p = bfs.front(); bfs.pop();
        int px = p.first, py = p.second, pd = dist[px][py] + 1;
        int t1 = min(px, y - py), t2 = min(py, x - px);
        int dx[] = {px, 0, px + t2, px - t1, x, px};
        int dy[] = {0, py, py - t2, py + t1, py, y};
        for (int i = 0; i < 6; i++) {
            if (pd > k || dist[dx[i]][dy[i]] != inf) continue;
            dist[dx[i]][dy[i]] = pd;
            bfs.push({dx[i], dy[i]});
        }
    }
    int ans = inf;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < 101; j++) {
            if (dist[i][j] <= k) {
                ans = min(ans, abs(i + j - m));
            }
        }
    }
    cout << ans << "\n";
}
/*
Type: BFS
Time Complexity: O(XY)
Algorithm:
Create a 2d matrix for each value of x and y.
Set every value to infinite and store the first time
you get that pair. Run BFS on every option until you 
go through K iterations. Go through the 2d matrix and 
find the pair that's the closest to the desired value.
*/