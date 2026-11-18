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
struct SCC {
    int n, ti, nc; // nc = # of SCCs
    vector<int> st, num, low;
    vector<vector<int>> adj;
    vector<bool> vis;
    SCC(int sz) {
        adj.resize(sz + 5), num.resize(sz + 5), 
        low.resize(sz + 5), vis.resize(sz + 5);
        n = sz;
    }
    void init() {
        ti = nc = 0, fill(all(num), -1);
        for (int i = 0; i < n; i++) {
            if (num[i] == -1) dfs(i);
        }
    }
    void dfs(int u) {
        num[u] = low[u] = ti++;
        st.push_back(u);
        vis[u] = true;
        for (int v : adj[u]) {
            if (num[v] == -1) dfs(v);
            if (vis[v]) smin(low[u], low[v]);
        }
        if (low[u] == num[u]) {
            for (int v = -1; v != u;) {
                v = st.back(), st.pop_back();
                low[v] = nc, vis[v] = false;
            }
            nc++;
        }
    }
    void compress() {
        vector<array<int, 2>> edges;
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) if (low[i] != low[j]) {
                edges.push_back({low[i], low[j]});
            }
        }
        sort(all(edges));
        edges.erase(unique(all(edges)), end(edges));
        adj = vector(nc, vector<int>());
        for (auto [u, v] : edges) {
            adj[u].push_back(v);
        }
    }
};
void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> e(m);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        e[i] = {--x, --y, w};
    }
    auto fn = [&](int x) -> bool {
        /**
         * Checks if you can have <= 1 nodes
         * have 0 indegree.
        */
        SCC scc(n);
        for (auto [u, v, w] : e) {
            scc.adj[u].push_back(v);
            if (w <= x) scc.adj[v].push_back(u);
        }
        scc.init(), scc.compress();
        vector<int> deg(scc.nc);
        for (int i = 0; i < scc.nc; i++) {
            for (int j : scc.adj[i]) {
                ++deg[j];
            }
        }
        int cnt = 0;
        for (int i : deg) {
            cnt += (i == 0);
        }
        return cnt <= 1;
    };
    int low = 0, high = 1e9;
    while (low < high) {
        int mid = (low + high) / 2;
        fn(mid) ? high = mid : low = mid + 1;
    }
    cout << (fn(low) ? low : -1) << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Edge Reverse (CF)
 * Binary search on the highest edge you can use.
 * For each edge that can be reversed, make it double sided.
 * Then, check if there's <= 1 SCCs with indegree 0.
 * 
 * NOTE: Why can you make each edge double sided? Because,
 * functionally, you only really need the edge to move one way 
 * (cuz you're essentially traversing down the tree.)
*/
/**
  * 1. Can a graph be constructed?
  *    - Think of relations
  *    - If an explicit graph is given,
  *      think of "additions" you can make.
  *    - Minimize the # of nodes / edges.
  * 2. How can we reuse information?
  *    - Like DP, but slightly more general.
  * 3. Prove/justify any observations.
  *    - At least, it should be easy mentally.
  * 4. For math formulas, try rewriting them.
  *    - Make it something easier to work with.
  * 5. Break down the problem, or maybe reframe it.
  *    - Can you make it into a simpler problem.
  * 6. Try multiple techniques.
  *    - DP, Greedy, Graph, etc.
*/