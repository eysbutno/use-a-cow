#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int mx[301][301][301], dp[301][301];
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);
	int n, m; cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int w, l, r;
		cin >> w >> l >> r;
		--l, --r;
		for (int j = l; j <= r; j++) {
			smax(mx[l][j][r], w);
		}
	}
	for (int k = 0; k < n; k++) {
		for (int l = k; l >= 0; l--) {
			for (int r = k; r < n; r++) {
				smax(mx[l][k][r], mx[l + 1][k][r]);
				smax(mx[l][k][r], mx[l][k][r - 1]);
			}
		}
	}
	for (int d = 0; d < n; d++) {
		for (int l = 0; l + d < n; l++) {
			int r = l + d;
			for (int k = l; k < r; k++) {
				smax(dp[l][r], dp[l][k] + dp[k + 1][r]);
			}
			for (int k = l; k <= r; k++) {
				smax(dp[l][r], dp[l][k - 1] + 
					 dp[k + 1][r] + mx[l][k][r]);
			}
		}
	}
	cout << dp[0][n - 1] << '\n';
}
/**
 * TASK: Greedy Pie Eaters.
 * Motivating Question: What is the most
 * amount of weight you can have in every range?
 * Answer: By doing range DP, you can merge ranges in 
 * the following manner:
 * dp[l][r] = max(dp[l][r], dp[l][k] + dp[k + 1][r]),
 * for any k >= l and k < r.
 * dp[l][r] = max(dp[l][r], dp[l][k - 1] + dp[k + 1][r] + mx[l][k][r]),
 * for any k >= l and k <= r.
 * The first transition is if you combine two ranges. Pretty
 * intuitive.
 * The second transition is if you add a cow who wants to eat
 * pie k, whose endpoints are in [l, k] and [k, r]. If you add
 * a cow this way, it's guaranteed to be optimal, and all the
 * cows will be satisfied.
*/