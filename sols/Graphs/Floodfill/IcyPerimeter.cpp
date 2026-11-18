#include <bits/stdc++.h>
using namespace std;

const int N = 1001; int s;
char grid[N][N]; bool visited[N][N];
int area = 0; int perimeter = 0;

void ff(int r, int c) {
    if (r < 0 || r >= s ||
        c < 0 || c >= s ||
        visited[r][c] || grid[r][c] != '#') {
        return;
    }
    perimeter += r == 0 || grid[r - 1][c] == '.';
    perimeter += r == s - 1 || grid[r + 1][c] == '.';
    perimeter += c == 0 || grid[r][c - 1] == '.';
    perimeter += c == s - 1 || grid[r][c + 1] == '.';
    area++; visited[r][c] = true;
    ff(r + 1, c); ff(r - 1, c); ff(r, c + 1); ff(r, c - 1);
}
int main() {
    ifstream fin("perimeter.in");
    ofstream fout("perimeter.out");
    fin >> s;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            fin >> grid[i][j];
        }
    }
    int a = 0, p = 0;
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < s; j++) {
            if (!visited[i][j] && grid[i][j] == '#') {
                ff(i, j);
            }
            if (area > a || (area == a && perimeter < p)) {
                a = area; p = perimeter;
            }
            area = 0; perimeter = 0;
        }
    }
    fout << a << " " << p << endl;
    return 0;
}