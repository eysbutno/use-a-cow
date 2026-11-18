#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 101;
const int INF = 1e9;
int dp[MAX][MAX][MAX];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("taming.in", "r", stdin);
    freopen("taming.out", "w", stdout);
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= n; k++) {
                dp[i][j][k] = INF;
            }
        }
    }
    dp[0][0][1] = (int) (a[0] > 0);
    for (int i = 1; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            for (int k = 1; k <= i + 1; k++) {
                if (j < i) {
                    // just the previous state
                    dp[i][j][k] = dp[i - 1][j][k];
                } else {
                    // brute force best previous breakout
                    int best = INF;
                    for (int l = 0; l < i; l++) {
                        ckmin(best, dp[i - 1][l][k - 1]);
                    }
                    dp[i][j][k] = best;
                }
                if (a[i] != i - j) {
                    dp[i][j][k]++;
                }
                // in case this day's log is wrong
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        int res = INF;
        for (int j = 0; j < n; j++) {
            ckmin(res, dp[n - 1][j][i]);
        }
        cout << res << '\n';
    }
}
/**
 * Time complexity:
 * O(N ^ 3).
 * 
 * Observations:
 * 1. The logs must form arithmetic
 * progressions, and must start with
 * zero.
 * 
 * Transitions:
 * If j < i: dp[i][j][k] = dp[i - 1][j][k].
 * Else: Brute force the previous breakout.
 * +1 if a[i] != i - j for obvious reasons.
 * 
 * Explanations:
 * If j < i, everything remains the same, so
 * you can just use the previous answer, plus
 * one if necessary.
 * 
 * If j = i: Brute forcing the previous location
 * works for obvious reasons.
*/