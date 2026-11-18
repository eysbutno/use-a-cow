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
    vector grid(n, vector(m, '*'));
    // # = black, . = white.
    int rc = 0, cc = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    // check 1: no "gaps" in rows.
    for (int r = 0; r < n; r++) {
        int cnt = 0;
        for (int c = 0; c < m; c++) {
            if (grid[r][c] == '.') continue;
            if (c == 0 || grid[r][c - 1] == '.') {
                ++cnt;
            }
        }
        if (cnt > 1) {
            cout << -1 << "\n";
            return;
        }
        rc += (cnt == 0);
    }
    // check 2: no "gaps" in columns.
    for (int c = 0; c < m; c++) {
        int cnt = 0;
        for (int r = 0; r < n; r++) {
            if (grid[r][c] == '.') continue;
            if (r == 0 || grid[r - 1][c] == '.') {
                ++cnt;
            }
        }
        if (cnt > 1) {
            cout << -1 << "\n";
            return;
        }
        cc += (cnt == 0);
    }
    if ((rc && !cc) || (!rc && cc)) {
        cout << -1 << "\n";
        return;
    }
    vector vis(n, vector(m, false));
    auto valid = [&](int r, int c) -> bool {
        return (r >= 0 && r < n &&
                c >= 0 && c < m &&
                !vis[r][c] && grid[r][c] == '#');
    };
    auto ff = [&](int r, int c, auto&& ff) -> void {
        vis[r][c] = true;
        int dr[]{1, -1, 0, 0}, dc[]{0, 0, -1, 1};
        for (int i = 0; i < 4; i++) {
            int r1 = r + dr[i], c1 = c + dc[i];
            if (valid(r1, c1)) ff(r1, c1, ff);
        }
    };
    int compCount = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!vis[i][j] && grid[i][j] == '#') {
                ++compCount, ff(i, j, ff);
            }
        }
    }
    cout << compCount << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: B. Monopole Magnets (CF)
 * Problem Statement:
 * Basically, you are given a grid and
 * are allowed to place Monopole Magnets.
 * Each row and column must have a south magnet.
 * A white square must be impossible to navigate to,
 * and a black square must be possible to navigate to.
 * 
 * Claim: Every black square can and should have a magnet
 * in it.
 * Proof: If this isn't the case, then there is no valid
 * coloring. AKA, there would be a gap like this:
 * #.#, or something. But in that case, even if a better
 * coloring existed, it wouldn't fulfill the "all rows all columns"
 * trait.
 * 
 * Claim: Any cell w/ an empty row & column will have a south magnet.
 * Proof: There's no reason not to have one...
 * 
 * Then, it's just # of connected components.
*/
/**
  * 1. Can a graph be constructed?
  *    - Think of relations
  *    - If an explicit graph is given,
  *      think of "additions" you can make.
  *    - Minimize the # of nodes / edges.
  * 2. How can we reuse information?
  *    - Like DP, but slightly more general.
  * 3. Prove/justify any observations.
  *    - At least, it should be easy mentally.
  * 4. For math formulas, try rewriting them.
  *    - Make it something easier to work with.
  * 5. Break down the problem, or maybe reframe it.
  *    - Can you make it into a simpler problem.
  * 6. Try multiple techniques.
  *    - DP, Greedy, Graph, etc.
*/