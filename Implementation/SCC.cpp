#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/**
 * Stolen from Benq. To get the component
 * of node i, do scc.comp[node]
 */
struct scc {
	int n, ti = 0;
	const vector<vector<int>> &adj;
	vector<int> disc, comp, st, comps;

	scc(const vector<vector<int>> &_adj)
		: n((int) _adj.size()), adj(_adj), disc(n), comp(n, -1) {
		for (int i = 0; i < n; i++) {
			if (!disc[i]) { dfs(i); }
		}
		reverse(begin(comps), end(comps));
	}

	int dfs(int x) {
		int low = disc[x] = ++ti;
		st.push_back(x);
		for (int y : adj[x]) {
			if (comp[y] == -1) { 
				low = min(low, disc[y] ?: dfs(y)); 
			}
		}
		if (low == disc[x]) {
			comps.push_back(x);
			for (int y = -1; y != x; ) {
                comp[y = st.back()] = x, st.pop_back();
            }
		}
		return low;
	}

	int id(int x) { return comp[x]; }
};