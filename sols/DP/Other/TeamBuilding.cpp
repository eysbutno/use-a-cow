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

const int N = 1e3;
const int MOD = 1e9 + 9;
ll prv[N][N], dp[N][N];
void calcPF(int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (i) prv[i][j] += prv[i - 1][j];
			if (j) prv[i][j] += prv[i][j - 1];
			if (i && j) prv[i][j] -= prv[i - 1][j - 1];
			prv[i][j] = (prv[i][j] + MOD) % MOD;
		}
	}
}
int rect(int r, int c) {
	if (r < 0 || c < 0) {
		return 0;
	}
	return (int) prv[r][c];
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	// freopen("team.in", "r", stdin);
	// freopen("team.out", "w", stdout);
	int n, m, k; cin >> n >> m >> k;
	vector<int> fj(n), fp(m);
	for (int& i : fj) cin >> i;
	for (int& i : fp) cin >> i;
	sort(all(fj)), sort(all(fp));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (fj[i] > fp[j]) {
				++prv[i][j];
			}
		}
	}
	calcPF(n, m);
	for (int i = 1; i < k; i++) {
		for (int f = i; f < n; f++) {
			for (int p = i; p < m; p++) {
				if (fj[f] > fp[p]) {
					dp[f][p] = rect(f - 1, p - 1);
				} else {
					break;
				}
			}
		}
		for (int f = 0; f < n; f++) {
			for (int p = 0; p < m; p++) {
				prv[f][p] = dp[f][p];
				dp[f][p] = 0;
			}
		}
		calcPF(n, m);
	}
	cout << prv[n - 1][m - 1] << '\n';
}
/**
 * DP it. Define the following:
 * dp[i][j] = # of ways to arrange everything,
 * if i is the cow FJ chooses and J is the cow
 * FP chooses. Then, for all k >= 2, use this
 * state transition:
 * 
 * Assert that FJ[i] > FP[j].
 * dp[i][j] = sum of all previous dp[k][l]
 * where k < i and l < j. (Kind of like
 * 2D prefix sums!)
*/