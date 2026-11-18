#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 998244353;
template<class T> void add(T& a, T b) {
    a += b, a %= MOD;
}
unordered_map<int, ll> dp[2];
void calc(int val) {
    for (auto [v, c] : dp[0]) {
        add(dp[1][val + v], c);
        if (v) add(dp[1][val - v], c);
    }
    swap(dp[0], dp[1]);
    dp[1].clear();
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    dp[0][a[1]] = 1;
    for (int i = 2; i < n; i++) {
        calc(a[i]);
    }
    ll res = 0;
    for (auto [v, w] : dp[0]) {
        add(res, w);
    }
    cout << res << '\n';
}
/**
 * Observation 1:
 * Once we perform an operation i,
 * the first i elements are unaffected.
 * 
 * Observation 2:
 * If we perform DP, the only state that
 * matters is the previous index, and the
 * final value.
 * 
 * Reasoning: All the prefixes with different
 * ending values are obviously distinct.
 * 
 * Note: There are probably faster ways to implement
 * this algorithm; using maps is just the easiest.
*/