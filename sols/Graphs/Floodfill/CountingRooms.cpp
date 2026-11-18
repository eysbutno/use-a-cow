#include <bits/stdc++.h>
using namespace std;

const int N = 1001;
char grid[N][N]; bool visited[N][N];
int row, col;
void ff(int r, int c) {
    if (r < 0 || c < 0 ||
    r >= row || c >= col ||
    visited[r][c] || grid[r][c] == '#') {
        return;
    }
    visited[r][c] = true;
    ff(r + 1, c); ff(r - 1, c);
    ff(r, c + 1); ff(r, c - 1);
}
int main() {
    cin >> row >> col;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cin >> grid[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (!visited[i][j] && grid[i][j] == '.') {
                ff(i, j); ans++;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
