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
void solve() {
    int n; cin >> n;
    string s; cin >> s;
    vector<ll> dp(n + 1);
    /**
     * dp[i] = result for all substrings
     *         starting at index i.
    */
    ll result = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '0') {
            // does not change prev result
            dp[i] = dp[i + 1];
        } else {
            // need at least one character for [i, i + 3)
            int ind = min(n, i + 3);
            dp[i] = dp[ind] + (n - i);
            // ^^ b/c every substring needs an extra 1
        }
        result += dp[i];
    }
    cout << result << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: D2. Sum over all Substrings.
 * Let's say we have a pattern like 101.
 * Then, the string 010 suffices. For
 * 110, 100 suffices. However, for 1001,
 * something like 1001 is required. So,
 * at every index, we only care about the
 * substring from [i, i + 3).
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/