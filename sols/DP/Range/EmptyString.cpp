#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

ll dp[505][505];
ll comb[255][255];
const int MOD = 1e9 + 7;
int add(int a, int b) {
    return (a + b) % MOD;
}
int mult(ll a, ll b) {
    return (int) ((a * b) % MOD);
}
int main() {
    string s; cin >> s;
    int n = s.length();
    comb[0][0] = 1;
    for (int i = 1; i <= n / 2; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            comb[i][j] = add(comb[i - 1][j], 
                            comb[i - 1][j - 1]);
        }
    }
    for (int i = 0; i < n; i++) {
        dp[i + 1][i] = 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j += 2) {
            for (int k = i + 1; k <= j; k += 2) {
                if (s[i] != s[k]) continue;
                int res = mult(mult(dp[i + 1][k - 1], dp[k + 1][j]), 
                    comb[(j - i + 1) / 2][(k - i + 1) / 2]);
                dp[i][j] = add(dp[i][j], res);
            }
        }
    }
    cout << dp[0][n - 1] << '\n';
}
/**
 * Think of the dp as seeing what the answer
 * is after adding a character i.
 * 
 * Define ok[i][j] to be if you can
 * successfully delete everything in 
 * this range, and dp[i][j] to be the 
 * # of ways to do this.
 * 
 * DP State Transitions:
 * Assert that s[i] == s[k].
 * dp[i][j] = sum of: dp[i + 1][k - 1] *
 * dp[k + 1][j] * (pairs in [l, r] choose 
 * pairs in [l, k]).
 * NOTE: Why multiply it by the combination?
 * Answer: That combination marks the # of ways
 * you can choose all the pairs, eventually.
*/