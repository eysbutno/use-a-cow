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
const int N = 2e5;
vector<int> adj[N];
ll a[N], sub[N], tot[N], res[N];
void dfs1(int u, int p) {
	sub[u] = 1;
	for (int i : adj[u]) {
		if (i != p) {
			dfs1(i, u);
			sub[u] += sub[i];
			tot[i] += (a[i] ^ a[u]) * sub[i];
		}
	}
}
void dfs2(int u, int p, ll sum) {
	res[u] = sum;
	for (int i : adj[u]) {
		if (i != p) {
			ll nxt = sum + (a[u] ^ a[i]) 
				   * (sub[0] - 2 * sub[i]);
			dfs2(i, u, nxt);
		}
	}
}
void solve() {
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		adj[--x].pb(--y);
		adj[y].pb(x);
	}
	dfs1(0, -1);
	ll sum = 0;
	for (int i = 0; i < n; i++) {
		sum += tot[i];
	}
	dfs2(0, -1, sum);
	for (int i = 0; i < n; i++) {
		cout << res[i] << ' ';
		res[i] = sub[i] = tot[i] = 0;
		adj[i].clear();
	}
	cout << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t; cin >> t;
	while (t--) solve();
}
/**
 * TASK: Tree XOR.
 * Idea: Solve for one root, reroot in O(1).
 * 
 * Claim: a ^ c != b ^ c, if a != b. Therefore,
 * you must traverse down the tree while making edits.
 * 
 * Proof: Pretty obvious that you can't make them
 * the same. The reasoning is (mostly) obvious.
 * 
 * Claim: The answer is just the following:
 * sum (i != root) sub_size[i] * (a[i] ^ a[parent]).
 * 
 * Proof: a[i] must equal it's subtree. Note that  this
 * sum must be calculated in order.
 * 
 * Claim: If we reroot from one node to another, the
 * answer only changes by the fact that we add a spell
 * between top and bottom.
 * 
 * Proof: The spell is applied to all vertices in the 
 * subtree. (A ^ C) ^ (B ^ C) is equivalent to A ^ B,
 * so you can apply this operation without making any
 * changes.
 * 
 * (Wow, I suck at bit operations...)
*/