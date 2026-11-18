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
    int n; cin >> n;
    vector c(n, vector(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }
    int timer = n; // counter
    vector<int> init(n);
    iota(all(init), 0);
    vector<int> salary(n * 2 + 1);
    vector<array<int, 2>> edges;
    auto dfs = [&](vector<int> leaves, 
                   auto&& dfs) -> int {
        if (sz(leaves) == 1) {
            int v = leaves[0];
            salary[v] = c[v][v];
            return v;
        }
        int mx = -1;
        for (int i : leaves) {
            smax(mx, c[leaves[0]][i]);
        }
        vector<vector<int>> sets = {{leaves[0]}};
        for (int i = 1; i < sz(leaves); i++) {
            int chosen = -1;
            for (int j = 0; j < sz(sets); j++) {
                if (c[leaves[i]][sets[j][0]] != mx) {
                    chosen = j;
                    break;
                }
            }
            if (chosen == -1) {
                sets.push_back({});
                chosen = sz(sets) - 1;
            }
            sets[chosen].push_back(leaves[i]);
        }
        int id = timer++;
        salary[id] = mx;
        for (auto &i : sets) {
            int v = dfs(i, dfs);
            edges.push_back({v, id});
        }
        return id;
    };
    int root = dfs(init, dfs);
    cout << timer << "\n";
    for (int i = 0; i < timer; i++) {
        cout << salary[i] << (i < timer - 1 ? " " : "\n");
    }
    cout << root + 1 << "\n";
    for (auto [u, v] : edges) {
        cout << u + 1 << " " << v + 1 << "\n";
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: D. Dogeforces (Codeforces)
 * Start from the root, and DFS down. We can
 * observe that for each subtree root, the "leaves"
 * can be divided into two distinct sets. So, we keep
 * on dividing until we reach each leaf.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/ 