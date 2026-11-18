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

int dp[5001][5001];
bool isPal[5001][5001];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    string s; cin >> s;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        isPal[i][i] = 1;
        isPal[i + 1][i] = 1;
        dp[i][i] = true;
    }
    for (int d = 1; d < n; d++) {
        for (int l = 0; l + d < n; l++) {
            int r = l + d;
            isPal[l][r] = isPal[l + 1][r - 1] 
                & s[l] == s[r];
            dp[l][r] = dp[l][r - 1] + dp[l + 1][r]
                - dp[l + 1][r - 1] + isPal[l][r];
        }
    }
    int q; cin >> q;
    while (q--) {
        int l, r; cin >> l >> r;
        cout << dp[l - 1][r - 1] << '\n';
    }
}
/**
 * Range DP it. 
 * DP State Transition:
 * dp[i][j] = dp[i][j - 1] + dp[i + 1][j] - 
 * dp[i + 1][j - 1] + isPal[i][j].
 * isPal[i][j] = isPal[i + 1][j - 1] & (s[i] == s[j]).
 * 
 * Base Cases: 
 * dp[i][i] = 1, isPal[i][i] = 1, isPal[i + 1][i] = 1.
 * NOTE: isPal[i + 1][i] = 1 is only when len = 2.
*/