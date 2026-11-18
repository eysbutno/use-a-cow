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

int dp[1001][1001];
template<class T> bool smin(T& a, T b) {
    return (b < a ? a = b, 1 : 0);
}
template<class T> bool smax(T& a, T b) {
    return (b > a ? a = b, 1 : 0);
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	int n; cin >> n;
	vector<int> a(n + 1), b(n + 1);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i <= n; i++) {
		cin >> b[i];
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			dp[i][j] = max({dp[i - 1][j - 1], 
				dp[i - 1][j], dp[i][j - 1]});
			if (abs(a[i] - b[j]) <= 4) {
				smax(dp[i][j], dp[i - 1][j - 1] + 1);
			}
		}
	}
	int res = 0;
	for (int i = 0; i <= n; i++) {
		smax(res, dp[n][i]);
	}
	cout << res << '\n';
}
/**
 * TASK: No Cross.
 * Observation 1:
 * If a_i -> b_i is one cross,
 * and another cross is a_j -> b_j,
 * then there can be no pairs where
 * a_i < a_j but b_i > b_j. Kind of
 * like inversions.
 * 
 * NOTE: We only care about the previous ID,
 * and the one it links to. Why? Because as
 * long as the previous ID < the current one,
 * it doesn't change the inversion status. So,
 * we base our transition off of the previous
 * cow's and this cow's answers.
 * 
 * On another note, you can also implement this
 * with a 1D array. I'm just too lazy to.
*/