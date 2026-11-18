#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MOD = 998244353;
void solve() {
    int n, k; cin >> n >> k;
    vector<vector<int>> dp(n + 1, 
        vector<int>(k + 1));
    dp[0] = vector<int>(k + 1, 1);
    int res = 0;
    for (int tot = 1; tot <= n; tot++) {
        for (int len = 1; len <= k; len++) {
            for (int prev = 1; prev * len <= tot && prev + len - 1 <= k; prev++) {
                dp[tot][len] += dp[tot - len * prev][prev];
                dp[tot][len] %= MOD;
            }
            if (tot == n) res += dp[tot][len], res %= MOD;
        }
    }
    cout << res << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Counting Binary Strings.
 * So, it's basically guaranteed that
 * each TC has a time complexity of like
 * NK or N^2 or something to that effect.
 * 
 * How can you count how many good substrings
 * a given string has? Well, it's just this:
 * For each 1 in the string, add (l + 1)(r + 1),
 * where l = 0s on the left, r = 0s on the right.
 * 
 * So, reformulate the problem to the following:
 * In how many ways can you construct an array a_i,
 * such that a_i <= k, and a_i * a_i+1 + a_i+1 * a_i+2...
 * until + a_n-1 * a_n is equal to EXACTLY n.
*/