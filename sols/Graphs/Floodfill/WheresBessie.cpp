#include <bits/stdc++.h>
using namespace std;

int n, R1, C1, R2, C2;
char grid[20][20];
struct Rect {
    int r1, c1, r2, c2;
    bool inside(Rect y) {
        return y.r1 <= r1 && y.c1 <= c1 
            && y.r2 >= r2 && y.c2 >= c2;
    }
};
void ff(int r, int c, char col, vector<vector<bool>>& vis) {
    if (r < R1 || r > R2 || c < C1 || c > C2
        || grid[r][c] != col || vis[r][c]) {
        return;
    }
    vis[r][c] = 1;
    ff(r + 1, c, col, vis), ff(r - 1, c, col, vis), 
    ff(r, c + 1, col, vis), ff(r, c - 1, col, vis);
}
bool isPCL(int r1, int c1, int r2, int c2) {
    R1 = r1, R2 = r2, C1 = c1, C2 = c2;
    vector<vector<bool>> vis(n, vector<bool>(n));
    vector<int> seen(26);
    for (int i = r1; i <= r2; i++) {
        for (int j = c1; j <= c2; j++) {
            if (!vis[i][j]) {
                ff(i, j, grid[i][j], vis);
                seen[grid[i][j] - 'A']++;
            }
        }
    }
    int cols = 0; bool is1 = 0, is2 = 0;
    for (int i : seen) {
        cols += (bool) i > 0;
        is1 |= i == 1;
        is2 |= i > 1;
    }
    return (cols == 2 && is1 && is2);
}
int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    vector<Rect> PCLs;
    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 < n; c1++) {
            for (int r2 = r1; r2 < n; r2++) {
                for (int c2 = c1; c2 < n; c2++) {
                    if (isPCL(r1, c1, r2, c2)) {
                        PCLs.push_back({r1, c1, r2, c2});
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < PCLs.size(); i++) {
        bool ok = 1;
        for (int j = 0; j < PCLs.size(); j++) {
            if (PCLs[i].inside(PCLs[j]) && i != j) {
                ok = 0; break;
            }
        }
        ans += ok;
    }
    cout << ans << "\n";
}