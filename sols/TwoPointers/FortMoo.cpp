#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

int pf[201][201], n, m;
int sum(int r1, int c1, int r2, int c2) {
    return pf[r2][c2] - pf[r1 - 1][c2]
        - pf[r2][c1 - 1] + pf[r1 - 1][c1 - 1];
}
int best(int r1, int r2) {
    vector<int> pos;
    for (int c = 1; c <= m; c++) {
        if (!sum(r1, c, r2, c)) {
            pos.pb(c);
        }
    }
    auto check = [&](int l, int r) {
        l = pos[l], r = pos[r];
        return (sum(r1, l, r2, l) +
                sum(r1, r, r2, r) + 
                sum(r1, l, r1, r) +
                sum(r2, l, r2, r) == 0);
    };
    int dc = 0, r = 0;
    for (int l = 0; l < sz(pos); l++) {
        smax(r, l);
        while (r + 1 < sz(pos) && 
            check(l, r + 1)) {
            ++r;
        }
        if (check(l, r)) {
            smax(dc, pos[r] - pos[l] + 1);
        }
    }
    return (r2 - r1 + 1) * dc;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("fortmoo.in", "r", stdin);
    freopen("fortmoo.out", "w", stdout);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            char x; cin >> x;
            pf[i][j] = (x == 'X') +
                pf[i - 1][j] + pf[i][j - 1]
                - pf[i - 1][j - 1];
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            smax(res, best(i, j));
        }
    }
    cout << res << '\n';
}
/**
 * Problem: Fort Moo.
 * Use 2D prefix sums, and fix
 * the left and right row bound.
 * 
 * You can use two pointers to find
 * the longest "column delta", for
 * each row pair.
*/