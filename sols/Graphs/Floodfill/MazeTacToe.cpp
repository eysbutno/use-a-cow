#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

const int MAX = 25;
int pow3[10], cnt;
set<int> res;
char grid[MAX][MAX];
bool vis[MAX][MAX][19683];
pair<int, char> loc[MAX][MAX];
bool check(int state, int inc) {
    vector<vector<char>> board(3, vector<char>(3, '.'));
    for (int i = 8; i >= 0; i--) {
        if (inc & (1 << i)) {
            int p = state / pow3[i];
            char val;
            if (!p) val = '.';
            if (p == 1) val = 'M';
            if (p == 2) val = 'O';
            board[i / 3][i % 3] = val;
            state -= p * pow3[i];
        }
    }
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == 'M' && board[i][1] == 'O' 
            && board[i][2] == 'O') return true;
        if (board[0][i] == 'M' && board[1][i] == 'O' 
            && board[2][i] == 'O') return true;
        if (board[i][2] == 'M' && board[i][1] == 'O' 
            && board[i][0] == 'O') return true;
        if (board[2][i] == 'M' && board[1][i] == 'O' 
            && board[0][i] == 'O') return true;
    }
    string a = "", b = "";
    for (int i = 0; i < 3; i++) {
        a += board[i][i], b += board[2 - i][2 - i];
    }
    if (a == "MOO" || b == "MOO") return true;
    a = "", b = "";
    for (int i = 0; i < 3; i++) {
        a += board[i][2 - i], b += board[2 - i][i];
    }
    if (a == "MOO" || b == "MOO") return true;
    return false;
}
void ff(int r, int c, int state, int inc) {
    if (r < 0 || r >= MAX || c < 0 || 
        c >= MAX || grid[r][c] == '#') {
        return;
    }
    if (grid[r][c] == 'C' && 
        !(inc & (1 << loc[r][c].f))) {
        inc += 1 << loc[r][c].f;
        if (loc[r][c].s == 'M') {
            state += pow3[loc[r][c].f];
        } else {
            state += 2 * pow3[loc[r][c].f];
        }
        if (check(state, inc)) {
            res.insert(state);
            vis[r][c][state] = 1;
            return;
        }
    }
    if (vis[r][c][state]) return;
    vis[r][c][state] = true;
    ff(r + 1, c, state, inc);
    ff(r - 1, c, state, inc);
    ff(r, c + 1, state, inc);
    ff(r, c - 1, state, inc);
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    pair<int, int> start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char a, b, c; cin >> a >> b >> c;
            if (a == 'B') {
                start.f = i, start.s = j;
            } else if (a == 'O' || a == 'M') {
                int r1 = (b - '0') - 1;
                int c1 = (c - '0') - 1;
                loc[i][j] = {r1 * 3 + c1, a};
                grid[i][j] = 'C';
            } else {
                grid[i][j] = a;
            }
        }
    }
    pow3[0] = 1;
    for (int i = 1; i < 10; i++) {
        pow3[i] = pow3[i - 1] * 3;
    }
    ff(start.f, start.s, 0, 0);
    cout << size(res) << '\n';
}
/*
Run floodfill on all the possible combos of moves.

Some implementation details:
If we have a location (i, j) (0 indexed),
then we'd compress that as i * 3 + j

I used an integer to see if a spot is occupied; you
could probably use a bitset, which would be easier

The most important thing:
Instead of compressing each board state as a list
of the moves played, compress it into an integer.
Each of the 9 locations has 3 possible values.
Given which spots are occupied, you can always determine
the board's current state
*/