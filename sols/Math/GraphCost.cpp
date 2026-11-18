#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n; ll m;
    cin >> n >> m;
    vector<ll> dp(n + 1);
    for (int i = n; i >= 1; i--) {
        ll mult = n / i;
        dp[i] = mult * (mult - 1) / 2;
        for (int j = i * 2; j <= n; j += i) {
            dp[i] -= dp[j];
        }
    }
    ll res = m;
    for (int i = n; i >= 2; i--) {
        ll use = min(dp[i] / (i - 1), m / (i - 1));
        m -= use * (i - 1), res += use;
    }
    cout << (m > 0 ? -1 : res) << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * E. Graph Cost (Codeforces)
 * The # of edges that can be made with a GCD
 * of x can be expressed as follows:
 * N choose 2, where N is the # of divisors 
 * of x, - dp[x * m], where m >= 2 and x * m <= n.
 * Then, the problem kind of becomes knapsack. Note
 * that because the # of operations you can do
 * for each GCD is non-decreasing, it always makes
 * the most sense to take the most "efficient" choice
 * at every turn.
*/