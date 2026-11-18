#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 1e9;
ll d[21], c[21], s[21][1000], dp[1 << 20];
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);
    ll n, l; cin >> n >> l;
    for (int i = 0; i < n; i++) {
        cin >> d[i] >> c[i];
        for (int j = 0; j < c[i]; j++) {
            cin >> s[i][j];
        }
    }
    fill(dp + 1, dp + (1 << n), -INF);
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            int bit = 1 << j;
            if (!(bit & i)) continue;
            int low = 0, high = c[j] - 1;
            while (low < high) {
                int mid = (low + high + 1) / 2;
                if (s[j][mid] <= dp[i - bit]) low = mid;
                else high = mid - 1;
            }
            // don't need bisearch but is faster
            if (s[j][low] <= dp[i - bit]) {
                smax(dp[i], s[j][low] + d[j]);
            }
        }
    }
    int res = INF;
    for (int i = 0; i < (1 << n); i++) {
        if (dp[i] >= l) smin(res, __builtin_popcount(i));
    }
    cout << (res != INF ? res : -1) << '\n';
}
/**
 * TASK: Moovie Mooving.
 * The answer requires you to build upon
 * the longest contiguous prefix you can make
 * with a given subset of chosen movies. So, we
 * can DP it.
 * 
 * NOTE: Bessie can exit the current moovie at 
 * ANY time she wants, so you always want to build
 * the longest prefix.
*/