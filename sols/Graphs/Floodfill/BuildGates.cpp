#include <bits/stdc++.h>
using namespace std;
// no workie
const int MX = 4003;
bool fence[MX][MX], visited[MX][MX];
int minr = 2001, minc = 2001, maxr = 2001, maxc = 2001;
void ff(int r, int c) {
    if (r < minr || c < minc ||
    r > maxr || c > maxc ||
    visited[r][c] || fence[r][c]) {
        return;
    }
    visited[r][c] = true;
    ff(r + 1, c); ff(r - 1, c);
    ff(r, c + 1); ff(r, c - 1);
}
int main() {
    freopen("gates.in", "r", stdin);
    freopen("gates.out", "w", stdout);
    int n; cin >> n;
    string f; cin >> f;
    int sr = 2001, sc = 2001;
    fence[2001][2001] = true;
    for (char i : f) {
        if (i == 'N') {
            sr--, fence[sr][sc] = 1;
            sr--, fence[sr][sc] = 1;
        } else if (i == 'S') {
            sr++, fence[sr][sc] = 1;
            sr++, fence[sr][sc] = 1;
        } else if (i == 'W') {
            sc--, fence[sr][sc] = 1;
            sc--, fence[sr][sc] = 1;
        } else {
            sc++, fence[sr][sc] = 1;
            sc++, fence[sr][sc] = 1;
        }
        fence[sr][sc] = 1;
        minr = min(minr, sr);
        maxr = max(maxr, sr);
        minc = min(minc, sc);
        maxc = max(maxc, sc);
    }
    minr--; minc--; maxr++; maxc++;
    int count = -1;
    for (int i = minr; i <= maxr; i++) {
        for (int j = minc; j <= maxc; j++) {
            if (!visited[i][j] && !fence[i][j]) {
                ff(i, j); count++;
            }
        }
    }
    cout << count << "\n";
    return 0;
}

/*
Type: Floodfill
Algorithm:
Keep on running floodfill every time you see a square
that's not visited and not a fence.

IMPORTANT OBSERVATIONS!!!
#1: You have to stretch out the graph by a factor of two to 
capture boxes like (1, 1), (1, 2), (2, 1), (2, 2)
#2: You have to expand the region by 1 on each side,
and also allow FF calls when equal to a maximum boundary
NOTE: is it possible to not reduce the search size? Probably.
However, this is terrible for your memory usage, so it's best to avoid
doing this. 
*/