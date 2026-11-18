#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

const int MAX = 
    1e3 + 1;
int n, m;
char grid[MAX][MAX];
int dist1[MAX][MAX], 
    dist2[MAX][MAX],
    moves[MAX][MAX];
int dr[]{0, 0, 1, -1},
    dc[]{1, -1, 0, 0};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    cin >> n >> m;
    pair<int, int> st;
    vector<pair<int, int>> monsters;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'M') {
                monsters.push_back({i, j});
            } else if (grid[i][j] == 'A') {
                st = {i, j};
            }
            dist1[i][j] = INT_MAX;
            dist2[i][j] = INT_MAX;
        }
    }
    queue<pair<int, int>> q;
    q.push(st);
    dist1[st.f][st.s] = 0;
    while (!q.empty()) {
        int r = q.front().f,
            c = q.front().s;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i],
                c1 = c + dc[i];
            if (r1 >= 0 && r1 < n
                && c1 >= 0 && c1 < m
                && grid[r1][c1] != '#'
                && dist1[r1][c1] > 
                dist1[r][c] + 1) {
                dist1[r1][c1] = dist1[r][c] + 1;
                q.push({r1, c1});
            }
        }
    }
    for (auto& i : monsters) {
        dist2[i.f][i.s] = 0;
        q.push(i);
    }
    while (!q.empty()) {
        int r = q.front().f,
            c = q.front().s;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i],
                c1 = c + dc[i];
            if (r1 >= 0 && r1 < n
                && c1 >= 0 && c1 < m
                && grid[r1][c1] != '#'
                && dist2[r1][c1] > 
                dist2[r][c] + 1) {
                dist2[r1][c1] = dist2[r][c] + 1;
                q.push({r1, c1});
            }
        }
    }
    q.push(st);
    pair<int, int> end = {-1, -1};
    while (!q.empty()) {
        int r = q.front().f,
            c = q.front().s;
        q.pop();
        if (dist1[r][c] >= dist2[r][c]) continue;
        if (r == 0 || r == n - 1 ||
            c == 0 || c == m - 1) {
            end = {r, c};
            while (!q.empty()) q.pop();
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i],
                c1 = c + dc[i];
            if (r1 >= 0 && r1 < n
                && c1 >= 0 && c1 < m
                && grid[r1][c1] != '#'
                && moves[r1][c1] == 0) {
                moves[r1][c1] = dr[i] * 2 + dc[i];
                q.push({r1, c1});
            }
        }
    }
    if (end.f == -1 && end.s == -1) {
        cout << "NO" << '\n';
        return 0;
    }
    int r = end.f, c = end.s;
    vector<char> res;
    while (r != st.f || c != st.s) {
        int m = moves[r][c];
        if (m == 2) {
            res.push_back('D');
            --r;
        } else if (m == 1) {
            res.push_back('R');
            --c;
        } else if (m == -1) {
            res.push_back('L');
            ++c;
        } else {
            res.push_back('U');
            ++r;
        }
    }
    cout << "YES" << '\n';
    cout << res.size() << '\n';
    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i];
    }
}
/*
Ugh, you're a monster!
I CAN SWALLOW A BOTTLE OF ALCOHOL-
Algorithm: Find shortest dist
from the player and the monsters
for each location. If there's a path out
where the monster's can't catch the player,
then you get your answer.
*/