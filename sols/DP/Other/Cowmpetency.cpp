#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int MOD = 1e9 + 7;
ll dp[101][10001];
ll expo(ll x, ll n) {
    x %= MOD;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n, q, c; cin >> n >> q >> c;
	map<int, int> mp = {{0, 0}};
	for (int i = 0; i < q; i++) {
		int a, h; cin >> a >> h;
		mp.count(h) ? smin(mp[h], a) : mp[h] = a;
	}
	vector<pii> itvs;
	for (auto [k, v] : mp) {
		itvs.pb({v, k});
	}
	q = sz(itvs) - 1;
	dp[0][0] = 1; // base case
	for (int i = 1; i <= q; i++) {
		ll pf = 0, g1 = itvs[i].f - itvs[i - 1].s, 
		   g2 = itvs[i].s - itvs[i].f - 1;
		for (int j = 1; j <= c; j++) {
			dp[i][j] = (dp[i][j - 1] + dp[i - 1][j - 1] * expo(j - 1, g1 + g2) % MOD +
                        pf * (expo(j - 1, g1) - expo(j - 2, g1)) % MOD * expo(j - 1, g2)) % MOD;
			if (dp[i][j] < 0) dp[i][j] += MOD;
			pf += dp[i - 1][j - 1], pf %= MOD;
		}
	}
	ll res = 0;
	for (int i = 1; i <= c; i++) {
		res += dp[q][i], res %= MOD;
	}
	cout << (res * expo(c, n - itvs.back().s)) % MOD << '\n';
}
/**
 * Let dp[i][j] to be the # of valid sequences up to restriction
 * i, with j being the value of h_i. Also, let u be the gap between
 * the two intervals, and v be the length of our current interval.
 * 
 * There are 3 cases in our DP.
 * Case 1: max(v) [1, h_i) < v_h_i - 1. Then, dp[i][j] += dp[i][j - 1].
 * Case 2: max(v) [1, a_i] = v_h_i - 1. Then, dp[i][j] += dp[i - 1][j - 1]
 * multiplied by (j - 1) ^ (u + v).
 * Case 3: max(v) (a_i, h_i) = v_h_i - 1, max(v) [1, a_i] < v_h_i - 1.
 * Then, dp[i][j] += prefix sum of dp[i - 1][j - 2] * (gaps with 1+ v_h_i - 1)
 * multiplied by the free choices in our (a_i, h_i) interval.
*/
/**
 * Key Problem Notes:
 * 1. Q and C are relatively small, while N is huge.
 * 2. **h_i is the FIRST index where a_i < h_i!!!**
 * 
 * For each interval, we assert the following:
 *  max(v) (a_i, h_i) <= max(v) [1, a_i] < h_i.
 * Proof: Any value before h_i must be less than it.
 * Values in [a_i, h_i) must be strictly less than
 * h_i and cannot be greater than a_i, otherwise such
 * a value would be the actual h_i. The other one is obvious.
 * 
 * Observation 1: 
 * 1. Assume (a_i, h_i) to be an interval [a_i, h_i].
 * All of these intervals are disjoint, minus intervals
 * where h_i = h_j, in which we consider the lower value of a.
 * Proof:
 * The problem asserts that there must be a valid construction.
 * For an interval to overlap, minus having equal endpoints, 
 * it would break property 2 of the problem. And we assert that
 * all numbers from [1, v_h_i) are less than v_h_i, so we can
 * discard the value of a that is larger.
 * 
 * This is obviously a DP task. We only need to care about
 * the restriction intervals, and the gaps between in our dp.
*/