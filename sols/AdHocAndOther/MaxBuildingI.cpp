#include <bits/stdc++.h>
using namespace std;

int pf[1001][1001];
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char c; cin >> c;
            pf[i][j] = pf[i - 1][j] + (c == '*');
        }
    }
    int res = 0;
    for (int r1 = 1; r1 <= n; r1++) {
        for (int r2 = r1; r2 <= n; r2++) {
            int best = 0, cur = 0;
            auto hasTree = [&](int c) {
                return pf[r2][c] - pf[r1 - 1][c] > 0;
            };
            for (int c = 1; c <= m; c++) {
                if (hasTree(c)) cur = 0;
                else smax(best, ++cur);
            }
            smax(res, (r2 - r1 + 1) * best);
        }
    }
    cout << res << '\n';
}
/**
 * TASK: Maximum Building I.
 * Fix the left and right, and
 * do a sweep.
*/