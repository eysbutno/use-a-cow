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
namespace SCC {
    int n, ti, nc;
    vector<int> st, num, low;
    vector<vector<int>> adj;
    vector<bool> vis; // lol
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
    void build(int sz) {
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
        for (auto [f, s] : edges) {
            adj[f].push_back(s);
        }
        st.clear(), num.clear(), low.clear(), vis.clear();
        // ^^ to free up memory, lol
    }
};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector occ(m, vector<int>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char c; cin >> c;
            if (c == '#') {
                occ[j].push_back(n - i - 1);
            }
        }
    }
    for (int i = 0; i < m; i++) {
        reverse(all(occ[i]));
    }
    vector<int> a(m);
    for (int &i : a) cin >> i;
    SCC::build(n * m);
    auto id = [&](int r, int c) -> int {
        return r * m + c;
    };
    auto addEdge = [&](pii v1, pii v2) -> void {
        // edge between v1 -> v2
        // v1 = {r1, c1}, v2 = {r2, c2}
        int id1 = id(v1.f, v1.s), 
            id2 = id(v2.f, v2.s);
        SCC::adj[id1].push_back(id2);
    };
    auto add = [&](int r, int c, pii og) -> void {
        // add any edges with row <= r.
        if (c < 0 || c >= m) return;
        int idx = upper_bound(all(occ[c]), r)
                - begin(occ[c]) - 1;
        if (idx >= 0 && idx < sz(occ[c]) && occ[c][idx] <= r) {
            addEdge(og, {occ[c][idx], c});
        }
    };
    for (int i = 0; i < m; i++) {
        for (int j : occ[i]) {
            pii cur = {j, i};
            add(j, i - 1, cur), add(j, i + 1, cur), add(j - 1, i, cur);
            int idx = upper_bound(all(occ[i]), j) - begin(occ[i]);
            if (idx < sz(occ[i]) && occ[i][idx] - j <= 1) {
                addEdge(cur, {occ[i][idx], i});
            }
        }
    }
    SCC::init();
    vector<int> mt;
    for (int i = 0; i < m; i++) {
        for (int j : occ[i]) {
            mt.push_back(SCC::low[id(j, i)]);
        }
    }
    sort(all(mt)), mt.erase(unique(all(mt)), end(mt));
    vector<int> deg(SCC::nc);
    SCC::compress();
    for (int i = 0; i < SCC::nc; i++) {
        for (int j : SCC::adj[i]) {
            ++deg[j];
        }
    }
    int res = 0;
    for (int i : mt) {
        if (!deg[i]) ++res;
    }
    cout << res << '\n';
}
/**
 * TASK: F2. Falling Sand (Easy).
 * Initially, draw a graph from one cell to another,
 * if one cell disturbs another. However, this would result
 * in a graph with at most (NM)^2 edges. Note that some edges
 * are completely redundant; if one block is disturbed, it will
 * disturb all the blocks under it. So, we only draw an edge between
 * each block and the highest block in adjacent columns it disturbs.
 * 
 * So, draw the graph. Note that it's a directed graph, and that 
 * there WILL be strongly connected components. Each component will
 * get triggered, so we can compress them and then DAG it.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Monotonicity? Concavity? Anything else?
  * 4. Prove/justify any observations.
  * 5. If there are 1e9+7 edge cases and it's
  *    impossible to implement, maybe it's not right.
  * 6. For math formulas, try rewriting them.
  * 7. Break down the problem, or maybe reframe it.
  * 8. Loop through common techniques... binary search?
  *    DP? DFS/BFS/Graphs? 
  * 9. If your idea is almost certainly right, try some
  *    optimization techniques. Small to large merging?
  *    Deleting unnecessary stuff? Using a set? IDK.
*/