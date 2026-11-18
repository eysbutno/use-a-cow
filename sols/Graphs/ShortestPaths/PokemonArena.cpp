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
    vector<int> c(n);
    for (int &i : c) cin >> i;
    vector a(n, vector(m, 0)); 
    vector p(m, vector<array<int, 2>>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
            p[j].push_back({a[i][j], i});
        }
    }
    vector rnk(m, vector(n, -1));
    // attribute i, rank j is id rnk[i][j]
    vector inv(m, vector(n, -1));
    // attribute i, pokemon j is rank inv[i][j]
    for (int i = 0; i < m; i++) {
        sort(all(p[i]));
        for (int j = 0; j < n; j++) {
            rnk[i][j] = p[i][j][1];
            inv[i][rnk[i][j]] = j;
        }
    }
    const ll INF = 1e18;
    vector dist(2, vector(n, vector(m, INF)));
    priority_queue<array<ll, 4>, vector<array<ll, 4>>, 
                   greater<>> pq;
    /**
     * Time, Node, Attribute, and whether or not this
     * current state is a "transition" (aka c[u] not factored),
     * or if it's "permanent" (aka it stays).
     * dist[Node][Attribute] will only store PERMANENT distances.
    */
    for (int i = 0; i < m; i++) {
        dist[1][0][i] = 0, pq.push({0, 0, i, 1});
    }
    vector<bool> vis(n);
    while (!pq.empty()) {
        auto [t, u, k, id] = pq.top(); pq.pop();
        if (t > dist[id][u][k]) continue;
        if (!id && smin(dist[1][u][k], t + c[u])) {
            pq.push({t + c[u], u, k, 1});
        }
        // propogate to other same node pairs.
        if (!vis[u] && id) {
            vis[u] = true;
            for (int i = 0; i < m; i++) {
                ll cur = dist[id][u][k];
                if (smin(dist[id][u][i], cur)) {
                    pq.push({dist[id][u][i], u, i, id});
                }
            }
        }
        // transition to a higher rank.
        int rank = inv[k][u];
        if (rank + 1 < n) {
            int nxt = rnk[k][rank + 1];
            if (smin(dist[0][nxt][k], t)) {
                pq.push({t, nxt, k, 0});
            }
        }
        // transition to a lower rank.
        if (rank > 0) {
            int nxt = rnk[k][rank - 1],
                dx = a[u][k] - a[nxt][k];
            if (smin(dist[0][nxt][k], t + dx)) {
                pq.push({t + dx, nxt, k, 0});
            }
        }
    }
    ll res = INF;
    for (int i = 0; i < m; i++) {
        smin(res, dist[1][n - 1][i]);
    }
    cout << res << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Pokemon Arena.
 * The problem is obviously a SP problem. Now, the
 * initial bash is obvious; just Dijkstra on the complete
 * graph, and directly compare stuff. To speed it up, 
 * we process each state as a Node-Attribute pair, and have only
 * one node battle with another attribute.
 * 
 * Now, on this graph, we only transition in two ways:
 * 1. Freely swap between pairs with the same node.
 * 2. Go to some "adjacent" pair with the same attribute.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/