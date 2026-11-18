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
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    vector adj(n, 0);
    vector dp(1 << n, vector(n, false));
    vector prv(1 << n, vector(n, -1));
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v; --u, --v;
        adj[u] |= (1 << v), adj[v] |= (1 << u);
        const int bit = (1 << u) | (1 << v);
        dp[bit][max(u, v)] = true;
        prv[bit][max(u, v)] = min(u, v);
    }
    for (int i = 0; i < (1 << n); i++) {
        // the current mask.
        vector<int> subset;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) subset.push_back(j);
        }
        if (sz(subset) <= 2) continue;
        for (int j = 0; j < sz(subset); j++) {
            // iterating over the "connector".
            for (int k = 1; k < sz(subset); k++) {
                // iterating over the "endpoint".
                if ((adj[subset[j]] >> subset[k] & 1) && 
                    dp[i ^ (1 << subset[k])][subset[j]]) {
                    dp[i][subset[k]] = true;
                    prv[i][subset[k]] = subset[j];
                }
            }
        }
    }
    auto process = [&](int mask, int edp) -> bool {
        vector<int> nxt(n, -1);
        // add every node inside the cycle.
        nxt[edp] = __builtin_ctz(mask);
        int cpy = mask;
        do {
            int p = prv[cpy][edp];
            cpy ^= (1 << edp);
            nxt[p] = edp;
            edp = p;
        } while (dp[cpy][edp]);
        for (int i = 0; i < n; i++) if (nxt[i] == -1) {
            int link = adj[i] & mask;
            if (__builtin_ctz(link) < n) {
                nxt[i] = __builtin_ctz(link);
            }
        }
        for (int i : nxt) {
            if (i == -1) return false;
        }
        cout << "YES" << "\n";
        for (int i : nxt) {
            cout << i + 1 << " ";
        }
        cout << "\n";
        return true;
    };
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            int lb = __builtin_ctz(i);
            if (dp[i][j] && (adj[j] >> lb & 1)
                && process(i, j)) {
                return 0;
            } 
        }
    }
    cout << "NO" << "\n";
}
/**
 * TASK: E. Routing (CF)
 * Premise of the problem: Construct a(v) to be
 * a functional graph with one cycle. Every node
 * must either be contained within this cycle, or
 * be directly connected to some node in the cycle.
 * Then, every node not in the cycle is pointed towards
 * the node in the cycle that it's connected to.
 * 
 * To check if a given cycle can work, we can prolly use
 * a bitmask DP. A naive state would be:
 * dp[mask][i][j] = if there's a (simple) path from i -> j,
 * and the subset of nodes is on that path. To drop a dimension,
 * just set i to be the "lowest" bit. After that, check every
 * possible path that loops back into itself.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/