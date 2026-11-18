#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
struct SCC {
    int n, ti;
    vector<int> num, id, stk;
    vector<vector<int>> adj, dag, comp;
    SCC(int _n) : n(_n), ti(0), num(n), 
                  id(n, -1), adj(n) {}
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    void init() {
        for (int u = 0; u < n; u++)
            if (!num[u]) dfs(u);
        dag.resize(comp.size());
        for (auto &c : comp)
            for (int u : c)
                for (int v : adj[u])
                    if (id[u] != id[v])
                        dag[id[u]].push_back(id[v]);
        for (auto &v : dag) {
            sort(v.begin(), v.end());
            v.erase(unique(v.begin(), v.end()), v.end());
        }
    }
    int dfs(int u) {
        int low = num[u] = ++ti;
        stk.push_back(u);
        for (int v : adj[u]) {
            if (!num[v])
                low = min(low, dfs(v));
            else if (id[v] == -1)
                low = min(low, num[v]);
        }
        if (low == num[u]) {
            comp.emplace_back();
            do {
                id[stk.back()] = sz(comp) - 1;
                comp.back().push_back(stk.back());
                stk.pop_back();
            } while (comp.back().back() != u);
        }
        return low;
    }
};
void solve() {
    int n, m; 
    cin >> n >> m;
    SCC scc(n);
    vector<bool> self(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        scc.addEdge(--u, --v);
        self[u] = self[u] | (u == v);
    }
    scc.init();
    int z = sz(scc.comp);
    vector<vector<int>> radj(z);
    for (int i = 0; i < z; i++) {
        for (int j : scc.dag[i]) {
            radj[j].push_back(i);
        }
    }
    const int INF = 1e9;
    vector<int> dp(z);
    for (int i = z - 1; i >= 0; i--) {
        dp[i] = (i == scc.id[0]);
        for (int j : radj[i]) {
            dp[i] += dp[j];
            smin(dp[i], INF);
        }
        if (dp[i] > 1 && dp[i] < INF) {
            dp[i] = 2;
        }
        bool canLoop = sz(scc.comp[i]) > 1 || 
                       self[scc.comp[i][0]];
        if (dp[i] > 0 && canLoop) {
            dp[i] = INF;
        }
    }
    for (int i = 0; i < n; i++) {
        int res = dp[scc.id[i]];
        cout << (res < INF ? res : -1) << " \n"[i == n - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: G. How Many Paths?
 * Compute SCCs, DP on DAG, etc...
*/ 