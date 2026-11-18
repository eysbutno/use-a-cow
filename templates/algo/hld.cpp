#include <bits/stdc++.h>
#include "data-structures/segtree.cpp"

using ll = long long;

/**
 * A (somewhat bad) HLD template. Notes:
 * - namespace is just cleaner IMO, would have loved to use a constructor for init tho...
 * - extends to subtree updates, since calculated tin and tout
 * - process just gives you all the segtree ranges to care about, you process manually
 */
namespace hld {
	int n, r, timer = 0;
	std::vector<std::vector<int>> adj;
	std::vector<int> par, sub, depth, rt, tin, tout;
 
	void dfs_sz(int v) {
		if (par[v] != -1) adj[v].erase(std::find(adj[v].begin(), adj[v].end(), par[v]));
		for (int &u : adj[v]) {
			par[u] = v, depth[u] = depth[v] + 1;
			dfs_sz(u);
			sub[v] += sub[u];
			if (sub[u] > sub[adj[v][0]]) std::swap(u, adj[v][0]);
		}
	}
 
	void dfs_hld(int v) {
		tin[v] = timer++;
		for (int u : adj[v]) {
			rt[u] = (u == adj[v][0] ? rt[v] : u);
			dfs_hld(u);
		}
 
        tout[v] = timer;
	}
 
	template <class B> void process(int u, int v, B op) {
		for (; rt[u] != rt[v]; v = par[rt[v]]) {
			if (depth[rt[u]] > depth[rt[v]]) std::swap(u, v);
			op(tin[rt[v]], tin[v]);
		}
 
		if (depth[u] > depth[v]) std::swap(u, v);
		op(tin[u], tin[v]);
	}
 
	void init(const std::vector<std::vector<int>> &_adj, int _r = 0) {
        n = _adj.size();
        adj = _adj;
        r = _r;
        par.assign(n, -1);
        sub.assign(n, 1);
        depth.resize(n);
        rt.resize(n);
        tin.resize(n);
        tout.resize(n);
        timer = 0;
		rt[r] = r;
		dfs_sz(r);
		dfs_hld(r);
	}
};