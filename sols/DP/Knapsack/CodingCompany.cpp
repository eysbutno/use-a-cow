#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
const int K = 5e3; // offset
const int N = 102;
ll dp[N][K * 2 + 1], 
   pre[N][K * 2 + 1];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, x; cin >> n >> x;
    vector<int> s(n);
    for (int& i : s) {
        cin >> i;
    }
    sort(begin(s), end(s));
    pre[0][K] = 1;
    ll res = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= x + K; k++) {
                dp[j][k] += pre[j][k];
                dp[j][k] += j * pre[j][k];
                if (k - s[i] >= 0) {
                    dp[j][k] += (j + 1) * (pre[j + 1][k - s[i]]);
                }
                if (j > 0) {
                    dp[j][k] += pre[j - 1][k + s[i]];
                }
                dp[j][k] %= MOD;
            }
        }
        for (int j = 0; j < n; j++) {
            for (int k = 0; k <= x + K; k++) {
                pre[j][k] = dp[j][k];
                dp[j][k] = 0;
            }
        }
    }
    for (int i = K; i <= x + K; i++) {
        res += pre[0][i];
        res %= MOD;
    }
    cout << res << '\n';
}
/**
 * dp[i][j][k] = # of ways to form teams from
 * the first i people, so there are j unfinished
 * teams and k penalty. Note that the first member
 * of a team contributes -s[f] to the penalties.
 * Why does this work? Because you have to close
 * this team... eventually.
 * 
 * Casework when adding a new person:
 * Case 1: Create a team of 1.
 * dp[i][j][k] += dp[i - 1][j][k]
 * Case 2: Start an unfinished team with i.
 * dp[i][j + 1][k - s[i]] += dp[i - 1][j][k]
 * Case 3: Finish an unfinished team with i.
 * dp[i][j - 1][k + s[i]] += j * dp[i - 1][j][k]
 * Case 4: Add i to an unfinished team.
 * dp[i][j][k] += j * dp[i - 1][j][k]
*/