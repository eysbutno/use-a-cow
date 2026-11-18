#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int MOD = 998244353;
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n, x; cin >> n >> x;
    vector nCr(n + 1, vector(n + 1, 0LL));
    for (int i = 0; i <= n; i++) {
        nCr[i][0] = 1, nCr[i][i] = 1;
        for (int j = 1; j <= i; j++) {
            nCr[i][j] = nCr[i - 1][j - 1] 
                      + nCr[i - 1][j];
            nCr[i][j] %= MOD;
        }
    }
    vector dp(n + 1, vector(x + 1, 0LL));
    dp[n][0] = 1; // 1 way to choose 0 heroes.
    for (int i = n; i >= 2; i--) {
        for (int j = 0; j <= x; j++) {
            // assume dp[i][j] is already calculated.
            if (!dp[i][j]) continue; // contributes 0.
            ll pw = 1, dmg = min(x, j + i - 1);
            for (int k = i; k >= 0; k--) {
                // k heroes will be left.
                dp[k][dmg] += ((dp[i][j] * pw % MOD) * 
                                nCr[i][i - k]) % MOD;
                dp[k][dmg] %= MOD;
                pw = (pw * (dmg - j)) % MOD;
            }
        }
    }
    ll res = 0;
    for (int i = 0; i <= x; i++) {
        res += dp[0][i], res %= MOD;
    }
    cout << res << "\n";
}
/**
 * TASK: Arena (Codeforces)
 * Note that each (alive) hero receives
 * the exact same damage. 
 * Let dp[i][j] be the # of ways to assign
 * the health values of the n - i dead heroes,
 * if j damage has currently been dealt. Then,
 * we can iterate over the # of heroes that must
 * die in the next round.
 * 
 * (Recurring theme of applying as many constraints
 * as possible to simplify the problem, lol)
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/