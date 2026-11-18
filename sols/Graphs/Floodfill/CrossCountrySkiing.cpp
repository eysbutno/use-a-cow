#include <bits/stdc++.h>
using namespace std;

const int N = 501; int row, col;
int grid[N][N]; bool visited[N][N], cp[N][N];
void ff(int r, int c, int dist, int prev) {
    if (r < 0 || r >= row || c < 0 || 
        c >= col || visited[r][c] || 
        abs(grid[r][c] - prev) > dist) {
        return;
    }
    visited[r][c] = true;
    ff(r + 1, c, dist, grid[r][c]); ff(r - 1, c, dist, grid[r][c]); 
    ff(r, c + 1, dist, grid[r][c]); ff(r, c - 1, dist, grid[r][c]);
}
int main() {
    ifstream fin ("ccski.in");
    ofstream fout ("ccski.out");
    fin >> row >> col; int highest = 0;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fin >> grid[i][j];
            highest = max(highest, grid[i][j]);
        }
    }
    int r, c;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            fin >> cp[i][j];
            if (cp[i][j]) {
                r = i; c = j;
            }
        }
    }
    int low = 0, high = highest;
    while (low < high) {
        int mid = low + (high - low) / 2;
        bool works = true; ff(r, c, mid, grid[r][c]);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (cp[i][j] && !visited[i][j]) {
                    works = false;
                }
                visited[i][j] = false;
            }
        }
        if (works) high = mid;
        else low = mid + 1;
    }
    fout << low << endl;
    return 0;
}