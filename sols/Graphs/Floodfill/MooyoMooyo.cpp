#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

void ff(int r, int c, int n, int col, int& sz, 
    vector<vector<int>>& grid, vector<vector<bool>>& vis) {
    if (r < 0 || r >= n || c < 0 || c >= 10 ||
        grid[r][c] != col || vis[r][c]) {
        return;
    }
    vis[r][c] = 1, sz++;
    ff(r + 1, c, n, col, sz, grid, vis);
    ff(r - 1, c, n, col, sz, grid, vis);
    ff(r, c + 1, n, col, sz, grid, vis);
    ff(r, c - 1, n, col, sz, grid, vis);
}
void rev(int r, int c, int n, int col, 
    vector<vector<int>>& grid, vector<vector<bool>>& vis) {
    if (r < 0 || r >= n || c < 0 || c >= 10 ||
        grid[r][c] != col || vis[r][c]) {
        return;
    }
    vis[r][c] = 1, grid[r][c] = 0;
    rev(r + 1, c, n, col, grid, vis);
    rev(r - 1, c, n, col, grid, vis);
    rev(r, c + 1, n, col, grid, vis);
    rev(r, c - 1, n, col, grid, vis);
}
void collapse(int n, vector<vector<int>>& grid) {
    for (int c = 0; c < 10; c++) {
        vector<int> ok;
        for (int r = n - 1; r >= 0; r--) {
            if (grid[r][c]) ok.push_back(grid[r][c]);
            grid[r][c] = 0;
        }
        for (int val = 0; val < size(ok); val++) {
            grid[n - 1 - val][c] = ok[val];
        }
    }
}
bool stage(int n, int k, vector<vector<int>>& grid) {
    vector<vector<bool>> vis(n, vector<bool>(10));
    vector<pair<int, int>> start;
    vector<int> count;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            if (!vis[i][j] && grid[i][j] != 0) {
                int sz = 0; start.push_back({i, j});
                ff(i, j, n, grid[i][j], sz, grid, vis);
                count.push_back(sz);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            vis[i][j] = 0;
        }
    }
    bool changed = 0;
    for (int i = 0; i < size(count); i++) {
        if (count[i] >= k) {
            int r = start[i].f, c = start[i].s;
            rev(r, c, n, grid[r][c], grid, vis);
            changed = 1;
        }
    }
    collapse(n, grid);
    return changed;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<vector<int>> grid(n, vector<int>(10));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            char num; cin >> num;
            grid[i][j] = (num - '0');
        }
    }
    for (int i = 0; i < (n * n) / k; i++) {
        bool done = !stage(n, k, grid);
        if (done) break;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 10; j++) {
            cout << grid[i][j];
        }
        cout << '\n';
    }
}