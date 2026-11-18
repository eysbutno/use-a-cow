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

int dp[301][301];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            dp[i][j] = j - i + 1;
        }
    }
    for (int len = 1; len < n; len++) {
        for (int l = 0; l + len < n; l++) {
            int r = l + len;
            for (int sp = l; sp < r; sp++) {
                smin(dp[l][r], dp[l][sp] + 
                    dp[sp + 1][r] - (a[l] == a[r]));
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
}
/**
 * Range DP it. When merging two
 * ranges [i, j] and [j + 1, k], use 
 * the following state transition:
 * dp[i][k] = min(dp[i][k], dp[i][j] +
 *      dp[j + 1][k] - (a[i] == a[k])).
 * 
 * Why does this work? Because as we 
 * add parts to a range, you can think of
 * it as adding "endpoints" for intervals.
*/