#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

const int MAX = 1e3 + 2;
int grid[MAX][MAX],
    pref[MAX][MAX];
struct Bound {
    int lr, ur, lc, uc;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);
    int n; cin >> n;
    map<int, Bound> rect;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (!rect.count(grid[i][j])) {
                rect[grid[i][j]] = {i, i, j, j};
            }
            Bound& bds = rect[grid[i][j]];
            bds.lr = min(bds.lr, i);
            bds.lc = min(bds.lc, j);
            bds.ur = max(bds.ur, i);
            bds.uc = max(bds.uc, j);
        }
    }
    rect.erase(0);
    for (auto& i : rect) {
        int lr = i.s.lr, ur = i.s.ur,
            lc = i.s.lc, uc = i.s.uc;
        pref[lr + 1][lc + 1]++;
        pref[lr + 1][uc + 2]--;
        pref[ur + 2][lc + 1]--;
        pref[ur + 2][uc + 2]++;
    }
    set<int> bad;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pref[i][j] += pref[i - 1][j] + 
                pref[i][j - 1] - pref[i - 1][j - 1];
            if (pref[i][j] > 1) bad.insert(grid[i - 1][j - 1]);
        }
    }
    cout << n * n - size(bad) - (size(rect) == 1) << '\n';
}
/*
TBH I shouldn't have peeked at the 
solution so many times...

Time Complexity: O(N^2)
Algorithm:
For each visible color, find out
the minimum rectangle that could
cause it to appear in the places
that it appears in. Then, use 2D
prefix sums to find the number of
"minimum" rectangles over a certain
cell. If there's more than one 
rectangle over a cell, we know
the color over that cell is incorrect.

Note: The edge case below is why we 
need to add the - size(rect) == 1:
4
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
*/