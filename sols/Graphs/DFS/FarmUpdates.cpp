#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define f first 
#define s second 

const int N = 1e5 + 1;
const int Q = 2e5;
vector<int> adj[N];
bool rem[Q], rel[N];
int res[N], cur;
void dfs(int u) {
	res[u] = cur, rel[u] = true;
	for (int i : adj[u]) {
		if (!rel[i]) dfs(i);
	}
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n, q; cin >> n >> q; cur = q;
	fill(rel + 1, rel + n + 1, true);
	vector<pii> edges, removed;
	for (int i = 0; i < q; i++) {
		char c; cin >> c;
		int x; cin >> x;
		if (c == 'A') {
			int y; cin >> y;
			edges.pb({x, y});
			removed.pb({-1, -1});
		} else if (c == 'R') {
			removed.pb(edges[x - 1]);
			rem[x - 1] = true;
		} else {
			removed.pb({0, x});
			rel[x] = false;
		}
	}
	for (int i = 1; i <= n; i++) {
		if (rel[i]) res[i] = q;
	}
	for (int i = 0; i < sz(edges); i++) {
		if (rem[i]) continue;
		auto [a, b] = edges[i];
		if (!rel[a]) swap(a, b);
		if (rel[a] && !rel[b]) dfs(b);
		adj[a].pb(b), adj[b].pb(a);
	}
	while (q--) {
		cur = q;
		auto [a, b] = removed[q];
		if (a == 0 && !rel[b]) {
			dfs(b);
		} 
		if (a != -1) {
			if (!rel[a]) swap(a, b);
			if (rel[a] && !rel[b]) dfs(b);
			adj[a].pb(b), adj[b].pb(a);
		}
	}
	for (int i = 1; i <= n; i++) {
		cout << res[i] << '\n';
	}
}
/**
 * TASK: Farm Updates.
 * Roads are only added between active farms,
 * so once a farm is irrelevant, it stays irrelevant.
 * Therefore, we can process the queries backwards.
*/