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
const int N = 2e5;
vector<int> adj[N];
ll a[N], dp[N], dp2[N],
   sub[N], sum[N], len[N];
void dfs1(int u, int p) {
	// preprocessing
	sum[u] = a[u], sub[u] = 1;
	for (int i : adj[u]) {
		dfs1(i, u);
		sum[u] += sum[i];
		sub[u] += sub[i];
		smax(len[u], len[i] + 1);
	}
}
void dfs2(int u, int p) {
	for (int i : adj[u]) {
		dfs2(i, u);
	}
	// calculating dp array
	sort(all(adj[u]), [&](int x, int y) {
		return sub[x] * sum[y] < sub[y] * sum[x];
	});
	ll t = 1;
	for (int i : adj[u]) {
		dp[u] += dp[i] + t * sum[i];
		t += sub[i] * 2;
	}
	// calculating dp2 array
	ll s1 = 0, s2 = 0;
	// sum, size of the subs
	dp2[u] = (sz(adj[u]) > 0) ? INT64_MAX : 0;
	for (int i = sz(adj[u]) - 1; i >= 0; i--) {
		int v = adj[u][i];
		s2 += sub[v];
		if (len[v] + 1 != len[u]) {
			s1 += sum[v];
			continue;
		}
		ll opt = dp[u] + dp2[v] - dp[v] - 2 * s1 * sub[v] 
			   + 2 * sum[v] * (s2 - sub[v]);
		smin(dp2[u], opt);
		s1 += sum[v];
	}
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n, t; cin >> n >> t;
    for (int i = 1; i < n; i++) {
        int p, v; cin >> p >> v;
        adj[--p].push_back(i), a[i] = v;
    }
	dfs1(0, -1), dfs2(0, -1);
	int path = (n - 1) * 2;
	if (t == 0) {
		cout << path << ' ' << dp[0];
	} else {
		cout << path - len[0] << ' ' << dp2[0];
	}
}
/**
 * TASK: Fertilizing Pastures.
 * Tree DP it. Define the following:
 * dp[i] = cheapest way to fertilize
 * everything in i's subtree, and come
 * back up to the top.
 * 
 * dp2[i] = cheapest way to fertilize
 * everything in i's subtree, while staying
 * down in the subtree (on the longest path).
*/