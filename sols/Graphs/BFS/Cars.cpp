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
    vector<array<int, 3>> edges(m);
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int t, x, y; cin >> t >> x >> y;
        edges[i] = {t, --x, --y};
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> color(n, -1);
    { // do the bipartite check
        bool bad = false;
        auto dfs = [&](int u, auto&& dfs) -> void {
            for (int v : adj[u]) {
                if (color[v] == -1) {
                    color[v] = !color[u];
                    dfs(v, dfs);
                } else if (color[v] == color[u]) {
                    bad = true;
                    return;
                }
            }
        };
        for (int i = 0; i < n; i++) {
            if (color[i] == -1) {
                color[i] = 0, dfs(i, dfs);
            }
        }
        if (bad) {
            cout << "NO" << "\n";
            return;
        }
    }
    // col[i] = 0: i is going left
    // col[i] = 1: i is going right
    int nodeCount = 0;
    vector<char> dir(n);
    vector<int> loc(n);
    { // toposort the cars
        adj = vector<vector<int>>(n);
        vector<int> inDeg(n);
        for (auto [t, x, y] : edges) {
            if (t == 1 && color[x]) {
                swap(x, y);
            }
            if (t == 2 && !color[x]) {
                swap(x, y);
            }
            adj[x].push_back(y);
            ++inDeg[y];
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (!inDeg[i]) q.push(i);
        }
        while (!q.empty()) {
            int u = q.front(); q.pop();
            loc[u] = nodeCount++;
            dir[u] = color[u] ? 'R' : 'L';
            for (int v : adj[u]) {
                if (!(--inDeg[v])) q.push(v);
            }
        }
    }
    if (nodeCount < n) {
        cout << "NO" << "\n";
    } else {
        cout << "YES" << "\n";
        for (int i = 0; i < n; i++) {
            cout << dir[i] << " " << loc[i] << "\n";
        }
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
    // KACHOWWWWWWWWWWWW
}
/**
 * TASK: E. Cars (Codeforces)
 * Interpret the problem as a graph. Initially,
 * draw an edge between two cars who have a relation.
 * 
 * Observation 1:
 * This graph MUST be bipartite. 
 * Justification:
 * Color a node black if it's facing left, and white if
 * it's facing right. If it's not bipartite, that means you
 * can't have the directions be different.
 * (I was too dumb to think of this, LMFAO).
 * 
 * Then, toposort to get the ordering. Observe that we can
 * arbitrarily assign directions, as any ordering is still valid
 * if we reverse all the cars, per se.
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/