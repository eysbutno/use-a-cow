#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * <O(n log n), O(1)> LCA implementation.
 * Can be reduced to O(n) build with O(n) init RMQ.
*/

#include "RMQ.cpp"

struct LCA {
    const int n;
    const vector<vector<int>> &adj;
    vector<int> tin, et, dep;
    RMQ<array<int, 2>> rmq;
    int timer = 0;

    void dfs(int u, int p) {
        tin[u] = timer, et[timer++] = u;
        for (int v : adj[u]) {
            if (v == p) { continue; }
            dep[v] = dep[u] + 1;
            dfs(v, u);
            et[timer++] = u;
        }
    }

    LCA(int _n, vector<vector<int>> &_adj) 
        : n(_n), adj(_adj), tin(n), et(2 * n), dep(n) {
        dfs(0, -1);
        vector<array<int, 2>> arr(2 * n);
        for (int i = 0; i < 2 * n; i++) {
            arr[i] = {dep[et[i]], et[i]};
        }
        rmq.init(arr);
    }

    int lca(int u, int v) const {
        if (tin[u] > tin[v]) { swap(u, v); }
        return rmq.qry(tin[u], tin[v])[1];
    }
    
    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
};