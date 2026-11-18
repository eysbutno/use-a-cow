#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
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
const int MAXN = 5e6 + 5;
namespace SCC {
    int ti, nc, num[MAXN], low[MAXN];
    bool visited[MAXN];
    vector<int> adj[MAXN], st;
    void dfs(int u) {
        num[u] = low[u] = ti++;
        st.push_back(u);
        visited[u] = true;
        for (int v : adj[u]) {
            if (num[v] == -1) dfs(v);
            if (visited[v]) {
                smin(low[u], low[v]);
            }
        }
        if (low[u] == num[u]) {
            int v = -1;
            while (u != v) {
                v = st.back();
                st.pop_back();
                low[v] = nc;
                visited[v] = false;
            }
            nc++;
        }
    }
    void init(int n) {
        memset(num, -1, sizeof(num));
        ti = nc = 0;
        for (int i = 0; i < n; i++) {
            if (num[i] == -1) dfs(i);
        }
    }
};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
	int n, m, d; cin >> n >> m >> d;
	auto id = [&](int v1, int v2) -> int {
		// v1 = value of d, v2 = node
		return v1 * n + v2;
	};
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; --u, --v;
		for (int j = 0; j < d; j++) {
			SCC::adj[id(j, u)].push_back(id((j + 1) % d, v));
		}
	}
	SCC::init(n * d);
	vector<int> cur(SCC::nc, -1),
				tot(SCC::nc);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			char c; cin >> c;
			int comp = SCC::low[id(j, i)];
			if (c == '1' && cur[comp] != i) {
				cur[comp] = i, ++tot[comp];
			}
		}
	}
	vector<array<int, 2>> edges;
	for (int i = 0; i < n * d; i++) {
		for (int v : SCC::adj[i]) {
			if (SCC::low[i] != SCC::low[v]) {
				edges.push_back({SCC::low[i], SCC::low[v]});
			}
		}
	}
	sort(all(edges));
	edges.erase(unique(all(edges)), end(edges));
	vector cadj(SCC::nc, vector<int>());
	for (auto [ff, ss] : edges) {
		cadj[ff].push_back(ss);
	}
	vector<int> dp(SCC::nc, -1);
	auto dfs = [&](int u, auto&& dfs) -> int {
		if (dp[u] != -1) return dp[u];
		dp[u] = tot[u];
		for (int v : cadj[u]) {
			smax(dp[u], tot[u] + dfs(v, dfs));
		}
		return dp[u];
	}; cout << dfs(SCC::low[0], dfs) << '\n';
}
/**
 * TASK: Museums Tour (CF).
 * Maintain a state of: Each day, and the museums
 * you can visit. So, construct a graph where 
 * each node is the current museum and day (mod d),
 * and each edge connects (u, t) to (v, (t + 1) % d).
 * Then, if we compute SCCs, the problem now becomes
 * a longest-path-on-DAG problem. Then, for each edge,
 * use it to unite each SCC.
 * 
 * Overcounting happens when on the path, there is some
 * pair (u, t) and (u, t') that show up on the path. However,
 * these two vertices will always be in the same SCC. Why? 
 * Because if there is such a path that leads to a different
 * value of t, you can repeat this path again and again until the
 * offset eventually makes it the same t.
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