#include <bits/stdc++.h>
using namespace std;

const int MAX = 2001;
int grid[MAX][MAX], pf1[MAX][MAX], 
    pf2[MAX][MAX], pf3[MAX][MAX];
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m, q; cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c; grid[i][j] = c == '1';
            pf1[i][j] = grid[i][j] + pf1[i - 1][j] + 
                pf1[i][j - 1] - pf1[i - 1][j - 1];
            pf2[i][j] = (grid[i][j] && grid[i - 1][j]) + 
                pf2[i - 1][j] + pf2[i][j - 1] - pf2[i - 1][j - 1];
            pf3[i][j] = (grid[i][j] && grid[i][j - 1]) + 
                pf3[i - 1][j] + pf3[i][j - 1] - pf3[i - 1][j - 1];
        }
    }
    while (q--) {
        int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
        int tot = pf1[r2][c2] - pf1[r2][c1 - 1] - 
            pf1[r1 - 1][c2] + pf1[r1 - 1][c1 - 1];
        int adj1 = pf2[r2][c2] - pf2[r2][c1 - 1] - 
            pf2[r1][c2] + pf2[r1][c1 - 1];
        int adj2 = pf3[r2][c2] - pf3[r2][c1] - 
            pf3[r1 - 1][c2] + pf3[r1 - 1][c1];
        cout << tot - adj1 - adj2 << "\n";
    }
}
/*
Algorithm:
Create a 2D prefix sum of all the blue squares, a
prefix sum for all the horizontally connected
pairs of squares, and a prefix sum for all the 
vertically connected pairs of squares.
The answer is the total squares - horiz. adj.
- vert. adj. squares for a subrectangle.

Why This Works:
All the squares are guaranteed to only have 1 path
from one square to another. This means that if we 
subtract the total squares - horiz - vert, then 
we won't overcount the horizontally and vertically adjacent
connections. 
*/