#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 201, 
    P = N * 18 + 1;
int dp[N][P];
template<class T> bool smin(T& a, T b) {
    return (b < a ? a = b, 1 : 0);
}
template<class T> bool smax(T& a, T b) {
    return (b > a ? a = b, 1 : 0);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k; cin >> n >> k;
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j < P; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    for (int i = 0; i < n; i++) {
        ll x; cin >> x;
        int t = 0, f = 0;
        while (x % 2 == 0) {
            ++t, x /= 2;
        }
        while (x % 5 == 0) {
            ++f, x /= 5;
        }
        for (int j = k - 1; j >= 0; j--) {
            for (int l = P - 1; l >= 0; l--) {
                if (dp[j][l] == -1) continue;
                int idx = min(P - 1, l + f);
                smax(dp[j + 1][idx], dp[j][l] + t);
            }
        }
    }
    int best = 0;
    for (int i = 0; i < P; i++) {
        smax(best, min(i, dp[k][i]));
    }
    cout << best << '\n';
}
/**
 * Observation 1:
 * Roundness is equal to the minimum
 * power of 2 and 5, for obvious reasons.
 * 
 * dp[i][j][k] = most # of 2s you can get by
 * running through the first i numbers, taking j numbers,
 * and having k powers of 5. Then,
 * dp[i + 1][j + 1][l + f[i]] = max(self, dp[i][j][l] + t[i]).
 * dp[i + 1][j][l] = max(self, dp[i][j][l]);
*/