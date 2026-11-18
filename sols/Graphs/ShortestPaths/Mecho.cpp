#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

const int MAX = 800;
char grid[MAX][MAX];
int n, s, dist[MAX][MAX],
    dr[4] = {1, -1, 0, 0},
    dc[4] = {0, 0, 1, -1};
pair<int, int> st, ed;
bool check(int mid) {
    int trav[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            trav[i][j] = 2e9;
        }
    }
    trav[st.f][st.s] = mid * s;
    queue<pair<int, int>> q;
    q.push(st);
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int r = p.f, c = p.s;
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i],
                newDist = trav[r][c] + 1;
            if (r1 >= 0 && r1 < n && c1 >= 0 && c1 < n 
                && newDist < trav[r1][c1] && newDist / s 
                < dist[r1][c1] && grid[r1][c1] != 'T') {
                trav[r1][c1] = newDist;
                q.push({r1, c1});
            }
        }
    }
    return trav[ed.f][ed.s] != 2e9;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    cin >> n >> s;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            dist[i][j] = 2e9;
            if (grid[i][j] == 'H') {
                q.push({i, j});
                dist[i][j] = 0;
            } else if (grid[i][j] == 'M') {
                st = {i, j};
            } else if (grid[i][j] == 'D') {
                ed = {i, j};
            } 
        }
    }
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        int r = p.f, c = p.s;
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (r1 >= 0 && r1 < n && c1 >= 0 && c1 < n 
                && dist[r][c] + 1 < dist[r1][c1] &&
                grid[r1][c1] != 'T' && grid[r1][c1] != 'D') {
                dist[r1][c1] = dist[r][c] + 1;
                q.push({r1, c1});
            }
        }
    }
    int low = 0, high = dist[st.f][st.s] - 1;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) {
            low = mid;
        } else {
            high = mid - 1;
        }
    }
    if (check(low)) cout << low << '\n';
    else cout << -1 << '\n';
}
/*
Woohoo I solved an IOI problem!
Time complexity: O(N^2logN)
^ Note: the log factor isn't strictly logN
Algorithm: Find the distance between each
point on the grid and any given bee. 
Binary search how much time Mecho can
wait. More implementation details in the code.
*/