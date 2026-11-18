#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const ll INF = 1e18;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
	int n, m; cin >> n >> m;
	vector<vector<pii>> adj(n);
	array<ll, 3> rebel;
	vector<ll> taken(n, INF);
	// case 1: ignore the backwards edge.
	for (int i = 0; i < m; i++) {
		ll u, v, w; cin >> u >> v >> w;
		--u, --v;
		if (u > v) {
			rebel = {u, v, w};
		} else {
			adj[u].pb({v, w});
			smin(taken[v], w);
		}
	}
	ll sum1 = 0;
	for (int i = 1; i < n; i++) {
		sum1 += taken[i];
	}
	// case 2: force the backwards edge.
	ll sum2 = rebel[2];
	adj[rebel[0]].pb({rebel[1], rebel[2]});
	smin(taken[rebel[1]], rebel[2]);
	for (int i = 1; i < n; i++) {
		if (i != rebel[1]) sum2 += taken[i];
	}
	vector<ll> dist(n, INF);
	for (int i = 0; i < n; i++) {
		for (auto& [v, w] : adj[i]) {
			w -= taken[v];
		}
	}
	priority_queue<pair<ll, ll>> pq;
	dist[0] = 0, pq.push({0, 0});
	while (!pq.empty()) {
		auto [t, u] = pq.top(); pq.pop();
		t = t * (-1);
		if (dist[u] != t) continue;
		for (auto [v, w] : adj[u]) {
			if (smin(dist[v], t + w)) {
				pq.push({-dist[v], v});
			}
		}
	}
	sum2 += dist[rebel[0]];
	cout << min(sum1, sum2) << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int t; cin >> t;
	while (t--) solve();
}
/**
 * TASK: Rebellious Edge.
 * We break the problem into two cases:
 * 1. Ignore the backwards edge.
 * 2. Force the backwards edge.
 * 
 * Case 1 is pretty simple. Case 2 is a
 * bit more involved.
 * 
 * Let the backwards edge be {u, v, w}.
 * 
 * The main idea is this: when we force
 * the backwards edge, all we are really
 * doing is forcing a path from 1 to node
 * u. Everything else proceeds as normal.
 * For every edge, we subtract the edge
 * weight that we took from the edge weight,
 * if that makes sense, to account for
 * the cost we have already spent. Then,
 * we simply Dijkstra the path from 1 to u.
*/