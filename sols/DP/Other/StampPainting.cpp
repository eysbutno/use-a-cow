#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
ll dp[1000001], pf[1000001];
ll expo(ll x, ll n) {
    x %= MOD;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = (res * x) % MOD;
        x = (x * x) % MOD;
        n >>= 1;
    }
    return res;
}
ll sub(ll a, ll b) {
    return (a - b + MOD) % MOD;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("spainting.in", "r", stdin);
    freopen("spainting.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    for (int i = 1; i < k; i++) {
        dp[i] = expo(m, i);
        pf[i] = (dp[i] + pf[i - 1]) % MOD;
    }
    for (int i = k; i <= n; i++) {
        dp[i] = ((m - 1) * sub(pf[i - 1], pf[i - k])) % MOD;
        pf[i] = (dp[i] + pf[i - 1]) % MOD;
    }
    cout << sub(expo(m, n), dp[n]) << '\n';
}
/**
 * Observation 1:
 * A painting is only possible if 
 * the longest sequence of a color
 * is >= k.
 * 
 * Reasoning:
 * If k = 1, we can obviously paint
 * each individual cell. Otherwise, we
 * can progressively layer the paintings,
 * and then cover up any "loose ends" with
 * a final stamp of length k.
 * 
 * Observation 2:
 * The answer is equal to M ^ N - all the
 * paintings that are impossible.
 * 
 * Define dp[i] to be the # of "illegal"
 * paintings, if there are i units painted.
 * 
 * dp[i] = (M - 1) * sum(j = 1 -> k - 1) dp[i - j].
 * Use prefix sums to calculate this in O(N).
 * Note: I use exponentiation, but it's super overkill.
*/