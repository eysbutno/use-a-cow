#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int& i : a) {
        cin >> i;
    }
    for (int& i : b) {
        cin >> i;
    }
    auto sq = [&](int x) {
        return x * x;
    };
    int tot = 0, sum = 0, pos = 0;
    for (int i = 0; i < n; i++) {
        tot += (n - 2) * (sq(a[i]) + sq(b[i]));
        sum += a[i] + b[i], pos += max(a[i], b[i]);
    }
    vector<vector<bool>> dp(n, 
        vector<bool>(pos + 1));
    dp[0][a[0]] = 1, dp[0][b[0]] = 1;
    for (int i = 0; i + 1 < n; i++) {
        for (int j = 0; j <= pos; j++) {
            if (dp[i][j]) {
                dp[i + 1][j + a[i + 1]] = 1;
                dp[i + 1][j + b[i + 1]] = 1;
            }
        }
    }
    int res = 1e9; // INF
    for (int i = 0; i <= pos; i++) {
        if (dp[n - 1][i]) {
            res = min(res, sq(i) + sq(sum - i));
        }
    }
    cout << tot + res << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Yet Another Minimization Problem.
 * Array cost formula can be reduced to the following expression:
 * (N - 2) * (sum 1..N) (a_i^2 + b_i^2) + (sum of a_i) ^ 2 + (sum of b_i) ^ 2.
 * The first term, for obvious reasons, is constant. So, we just need to
 * optimize the second two terms.
 * 
 * Okay, so the strat is to
 * brute force all the sums of a_i, in turn also getting b_i's sum. 
 * Define dp[i][j] to be if there's some set of operations that would
 * allow the prefix of 1 to i, to equal j. If dp[n][the #] is true, consider
 * that as a result.
 * 
 * NOTE: You could either bitset and or use a 1D array. I was too
 * lazy to implement this though.
*/