#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second

const int MAX = 101;
vector<pair<int, int>> sw[MAX][MAX];
bool on[MAX][MAX], vis[MAX][MAX];
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
void ff(int r, int c) {
    if (r <= 0 || r >= MAX || c <= 0 ||
        c >= MAX || !on[r][c] || vis[r][c]) {
        return;
    }
    vis[r][c] = 1;
    for (auto [f, s] : sw[r][c]) {
        on[f][s] = 1;
        for (int j = 0; j < 4; j++) {
            if (vis[f + dr[j]][s + dc[j]]) {
                ff(f, s);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        ff(r + dr[i], c + dc[i]);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        sw[x][y].push_back({a, b});
    }
    on[1][1] = 1; 
    ff(1, 1);
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            ans += on[i][j];
        }
    }
    cout << ans << '\n';
}
/*
Type: Floodfill
Algorithm: 
First, turn on all the lights in the room you're visiting
Then, check each room that you just turned on.
Is it adjacent to a room that Bessie has visited/is on?
If so, call the f() function on that room.
*/