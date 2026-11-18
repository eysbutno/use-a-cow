#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

const int MAX = 501;
int grid[MAX][MAX], pf[MAX][MAX];
int calcArea(int r1, int c1, int r2, int c2) {
    return pf[r2][c2] - pf[r1 - 1][c2]
        - pf[r2][c1 - 1] + pf[r1 - 1][c1 - 1];
}
ll solve(int n, int m) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (grid[i][j] >= m) {
                pf[i][j] = 1;
            } else {
                pf[i][j] = 0;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            pf[i][j] += pf[i - 1][j] + 
                pf[i][j - 1] - pf[i - 1][j - 1];
        }
    }
    ll ans = 0;
    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            int running = 0;
            for (int c = 1; c <= n; c++) {
                int res = calcArea(r1, c, r2, c);
                if (res < r2 - r1 + 1) {
                    running = 0;
                } else {
                    ans += ++running;
                }
            }
        }
    }
    return ans;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> grid[i][j];
        }
    }
    cout << solve(n, 100) - solve(n, 101) << '\n';
}