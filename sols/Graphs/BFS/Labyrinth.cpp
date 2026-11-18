#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

const int MAX = 1001;
bool vis[MAX][MAX];
char grid[MAX][MAX];
int path[MAX][MAX];
int main() {
    int n, m; cin >> n >> m;
    pair<int, int> start, end;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                start = {i, j};
            }
            if (grid[i][j] == 'B') {
                end = {i, j};
            }
        }
    }
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    char dir[] = {'D', 'U', 'R', 'L'};
    queue<pair<int, int>> q; 
    q.push(start);
    vis[start.f][start.s] = 1;
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int r = p.f + dx[i], c = p.s + dy[i];
            if (r >= 0 && r < n &&
                c >= 0 && c < m &&
                !vis[r][c] && grid[r][c]
                != '#') {
                vis[r][c] = 1; path[r][c] = i;
                q.push({r, c});
            }
        }
    }
    if (vis[end.f][end.s]) {
        vector<int> route;
        while (end != start) {
            int r = path[end.f][end.s];
            route.push_back(r);
            end.f -= dx[r], end.s -= dy[r];
        }
        reverse(route.begin(), route.end());
        cout << "YES" << "\n";
        cout << route.size() << "\n";
        for (int i : route) cout << dir[i];
    } else {
        cout << "NO" << "\n";
    }
    return 0;
}
/*
Type: BFS
Algorithm:
First, run BFS to explore the entire grid.
While running BFS, assign a value that
shows what the previous square was. Backtrack
to find the result.

NOTE:
The strategy of noting what came before is
MUCH MORE EFFECTIVE than storing a string for each BFS
path. Using a queue with strings TLE's.
*/