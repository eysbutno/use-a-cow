#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * LCA tree using binary lifting and stuff. 
 * Does basically everything needed. If more capability
 * is needed from the std::vectors, then maybe just copy the code
 * snippets.
 */
struct LCA {
    const int n, LG;
    const std::vector<std::vector<int>> &adj;
    std::vector<std::vector<int>> lift;
    std::vector<int> dep, tin, tout;
    int timer = 0;

    void dfs(int u, int p) {
        tin[u] = timer++;
        if (p != -1) {
            lift[0][u] = p;
            dep[u] = dep[p] + 1;
        }
        for (int i = 1; i < LG; i++) {
            lift[i][u] = lift[i - 1][lift[i - 1][u]];
        }
        for (int v : adj[u]) {
            if (v != p) { dfs(v, u); }
        }
        tout[u] = timer - 1;
    }

    LCA(const std::vector<std::vector<int>> &adj) 
        : n(adj.size()), LG(1 + std::__lg(n)), adj(adj),
          lift(LG, std::vector<int>(n)), dep(n), tin(n), tout(n) {
        dfs(0, -1);
    }

    bool is_anc(int u, int v) {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) {
        if (is_anc(u, v)) { return u; }
        if (is_anc(v, u)) { return v; }
        for (int i = LG - 1; i >= 0; i--) {
            if (!is_anc(lift[i][u], v)) {
                u = lift[i][u];
            }
        }
        return lift[0][u];
    }

    int kth(int u, int k) {
        for (int i = 0; i < LG; i++) {
            if (k >> i & 1) {
                u = lift[i][u];
            }
        }
        return u;
    }

    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};