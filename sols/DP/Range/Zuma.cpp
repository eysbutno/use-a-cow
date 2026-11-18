#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int INF = 1e9;
int dp[501][501];
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
int main() {
    int n; cin >> n;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i], dp[i][i] = 1;
    }
    for (int d = 1; d < n; d++) {
        for (int l = 0; l + d < n; l++) {
            int r = l + d;
            dp[l][r] = 1 + dp[l + 1][r];
            if (c[l] == c[l + 1]) {
                smin(dp[l][r], dp[l + 2][r] + 1);
            }
            for (int k = l + 2; k <= r; k++) {
                if (c[l] != c[k]) continue;
                smin(dp[l][r], dp[l + 1][k - 1] + dp[k + 1][r]);
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
}
/**
 * TASK: Zuma (CF).
 * Define dp[i][j] to be minimum seconds
 * to delete everything in the range [i, j].
 * 
 * The DP? Apparently it's... BASHING!!
 * Default: dp[l][r] = dp[l + 1][r] + 1. (Duh).
 * Case 2: a[l] = a[l + 1], then you can delete
 * these two consecutively in one operation.
 * Finally, try splitting up the array into two
 * partitions, in order to get your result.
*/