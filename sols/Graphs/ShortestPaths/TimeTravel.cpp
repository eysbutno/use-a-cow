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
const int N = 2e5 + 1;
const int INF = 1e9;
vector<pii> adj[N];
vector<int> occ[N];
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n, t; cin >> n >> t;
	for (int i = 1; i <= t; i++) {
		int m; cin >> m;
		while (m--) {
			int x, y; cin >> x >> y;
			adj[x].pb({y, i});
			adj[y].pb({x, i});
		}
	}
	int k; cin >> k;
	for (int i = 1; i <= k; i++) {
		int x; cin >> x;
		occ[x].pb(i);
	}
	vector<int> time(n + 1, INF);
	time[1] = 0; // for upper_bound s tuff
	priority_queue<pii> pq;
	pq.push({0, 1});
	while (!pq.empty()) {
		auto [t, u] = pq.top(); pq.pop();
		if (-t != time[u]) continue;
		for (auto [v, m] : adj[u]) {
			int nxt = upper_bound(all(occ[m]), time[u])
					- begin(occ[m]);
			if (nxt < sz(occ[m])) {
				nxt = occ[m][nxt];
			} else {
				continue;
			}
			if (nxt < time[v]) {
				time[v] = nxt;
				pq.push({-nxt, v});
			}
		} 
	}
	cout << (time[n] != INF ? time[n] : -1);
}
/**
 * TASK: Time Travel (CF).
 * Dijkstra + upper_bound usage. Pretty
 * simple.
 * 
 * Kind of cool tidbit, but this shows Dijkstra's
 * utility - it doesn't strictly need to be edge
 * weights.
*/