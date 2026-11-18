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

bool reach[51][51], use[51];
void dfs(int u, int s) {
	reach[s][u] = true;
	for (int m = 1; m <= 50; m++) {
		int v = u % m;
		if (!reach[s][v] && !use[m]) {
			dfs(v, s);
		}
	}
}
void recalc(vector<int>& a) {
	for (int i = 0; i <= 50; i++) {
		for (int j = 0; j <= 50; j++) {
			reach[i][j] = false;
		}
	}
	for (int i = 0; i < sz(a); i++) {
		dfs(a[i], a[i]);
	}
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n; cin >> n;
	vector<int> a(n), b(n);
	for (int& i : a) {
		cin >> i;
	}
	for (int& i : b) {
		cin >> i;
	}
	recalc(a);
	for (int i = 0; i < n; i++) {
		if (!reach[a[i]][b[i]]) {
			cout << -1 << '\n';
			return 0;
		}
	}
	ll res = 0;
	use[50] = true;
	for (int i = 49; i >= 0; i--) {
		recalc(a);
		for (int j = 0; j < n; j++) {
			if (!reach[a[j]][b[j]]) {
				res |= 1LL << (i + 1);
				use[i + 1] = false;
			}
		}
		use[i] = true;
	}
	cout << res << '\n';
}
/**
 * TASK: Remainder Game.
 * Observation 1: We must choose our values
 * of k in descending order.
 * Proof: 2^k > sum (i -> 1....k - 1) (2^i).
 * 
 * Observation 2: When choosing if to use a value
 * of k or not, we only use it IF there's an element
 * that specifically requires it.
 * 
 * So, with that figured out, you can solve this task
 * in the following manner: 
 * 1. Iterate on values of k under the value of k
 * you choose. If there's a node that cannot reach
 * b_i with these, but can with this edge, then use
 * this value of k.
 * 
 * NOTE: When running DFS, you have to make sure your 
 * algorithm accounts for edges > your value of k that
 * you can use (k's that have been added to your "set")
*/