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
void solve() {
    int n, m; cin >> n >> m;
    map<int, vector<int>> comp;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        comp[c].push_back(--u);
        comp[c].push_back(--v);
        adj[u].push_back(c);
        adj[v].push_back(c);
    }
    int st, ed; 
    cin >> st >> ed;
    --st, --ed;
    vector<int> dist(n, m + 1);
    priority_queue<array<int, 2>> pq;
    dist[st] = 0, pq.push({0, st});
    while (!pq.empty()) {
        auto [t, u] = pq.top(); pq.pop();
        if ((t *= -1) != dist[u]) continue;
        for (int col : adj[u]) {
            /**
             * v will be in a different line,
             * because we're processing everything
             * at the same time.
            */
            for (int v : comp[col]) {
                if (smin(dist[v], t + 1)) {
                    pq.push({-dist[v], v});
                }
            }
            comp[col].clear(); // everything processed
        }
    }   
    assert(dist[ed] <= m);
    cout << dist[ed] << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: G. Rudolf and Subway (CF)
 * Note that because travelling along a subway line
 * costs 0 changes, that we can essentially view
 * each subway line as a node of sorts. Then, the 
 * answer is just the shortest path between any 
 * subway line containing b, and any subway line 
 * containing e.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/ 