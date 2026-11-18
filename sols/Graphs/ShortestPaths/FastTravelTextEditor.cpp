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
const int MX = 676; // hash(v) < MX.
const int INF = 1e9; // infinity
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    string s; cin >> s;
    int n = s.length();
    auto hash = [&](int idx) -> int {
        int x = s[idx - 1] - 'a', 
            y = s[idx] - 'a';
        return x * 26 + y;
    };
    vector adj(MX, vector<int>());
    for (int i = 1; i < n; i++) {
        adj[hash(i)].push_back(i);
    }
    vector sp(MX, vector(n, INF));
    for (int i = 0; i < MX; i++) {
        if (!sz(adj[i])) continue;
        queue<int> q;
        for (int j : adj[i]) {
            sp[i][j] = 0;
            q.push(j);
        }
        set<int> proc = {i};
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int dx : array<int, 2>{1, -1}) {
                // moving left or right.
                if (u + dx >= 1 && u + dx < n && 
                    smin(sp[i][u + dx], sp[i][u] + 1)) {
                    q.push(u + dx);
                }
            }
            // moving along indices in the "component"
            if (!proc.count(hash(u))) {
                for (int v : adj[hash(u)]) {
                    if (smin(sp[i][v], sp[i][u] + 1)) {
                        q.push(v);
                    }
                }
                proc.insert(hash(u));
            }
        }
    }
    int m; cin >> m;
    auto query = [&](int x, int y) -> int {
        int res = abs(y - x); // without jumping.
        for (int i = 0; i < MX; i++) {
            smin(res, sp[i][x] + sp[i][y] + 1);
        }
        return res;
    };
    while (m--) {
        int x, y; cin >> x >> y;
        cout << query(x, y) << "\n";
    }
}
/**
 * TASK: E. Fast Travel Text Editor.
 * Group up all vertices with the same x and y values.
 * Then, we can brute force every "intermediate" group
 * of vertices/positions, for each query. Note that this
 * always works because the trivial solution of moving left
 * or right is already covered.
 * 
 * (To do this, we calculate the distance from every "group"
 * or x y pair, to every position)
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