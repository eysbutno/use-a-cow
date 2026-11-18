#include <bits/stdc++.h>
using namespace std;
#define ll long long 
#define f first 
#define s second 

bool grid[1001][1001];
int cnt(int r1, int r2, int c1, int c2) {
    int res = 0;
    for (int i = r1; i < r2; i++) {
        for (int j = c1; j < c2; j++) {
            res += grid[i][j];
        }
    }
    return res;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    freopen("leftout.in", "r", stdin);
    freopen("leftout.out", "w", stdout);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string row; cin >> row;
        for (int j = 0; j < n; j++) {
            if (row[j] == 'R') grid[i][j] = 0;
            else grid[i][j] = 1;
        }
    }
    for (int i = 0; i < n; i++) {
        if (!grid[i][0]) {
            for (int j = 0; j < n; j++) {
                grid[i][j] = !grid[i][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!grid[0][i]) {
            for (int j = 0; j < n; j++) {
                grid[j][i] = !grid[j][i];
            }
        }
    }
    // the first row and first
    // column are all 1's
    int rest = cnt(1, n, 1, n);
    if (rest == 0) {
        cout << "1 1" << '\n';
        return 0;
    }
    if (rest == (n - 1) * (n - 1)) {
        cout << -1 << '\n';
        return 0;
    }
    cout << rest << '\n';
    for (int i = 0; i < n; i++) {
        int res = cnt(0, n, i, i + 1);
        if (res == 0) {
            cout << 1 << ' ' << i + 1 << '\n';
            return 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int res = cnt(i, i + 1, 0, n);
        if (res == 0) {
            cout << i + 1 << ' ' << 1 << '\n';
            return 0;
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (!grid[i][j]) {
                cout << i + 1 << ' ' << j + 1 << '\n';
                return 0;
            }
        }
    }
}
/*
Note: Fails TC's 9 and 11. Nice.

There is only one small invariant condition.
If we have a 2x2 rectangle where three cows agree
and one cow disagrees, it's guaranteed that there can
never be a solution.

Reasoning:
Say we have an example rectangle:
11
01
No matter how we toggle the rows or
columns, toggling a row or column
that affects the disagreeing cow 
will make another cow in the rectangle
disagree.

Because of this, we'll first toggle
it in a manner where if there isn't
a "bad" rectangle, so the obvious
strategy is to flip all the rows
with the first cow as R, and all the
columns with the first cow as R.

Conditions for the solution:
All except the cows in the first
row or first column are in the 
wrong way: the 1 1 cow is wrong
because it being in disagreement
forces the first row/column to be
toggled incorrectly.

All of the cows are correct:
There is no "bad" cow.

Only the first cow in a row/column
disagrees with the rest of their cows:
That cow is the bad one.

If none of the previous conditions are met,
just pick the first cow that is wrong
because it's obviously mismatched.
*/