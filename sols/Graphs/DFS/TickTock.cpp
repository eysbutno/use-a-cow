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
const int MOD = 1e9 + 7;
ll expo(ll x, ll n, ll m = MOD) {
    ll res = 1; x %= m;
    for (; n; n >>= 1, x = (x * x) % m) {
        if (n & 1) res = (res * x) % m;
    }
    return res;
}
void solve() {
    int n, m, h; 
    cin >> n >> m >> h;
    vector a(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector adj(n, vector<pii>());
    int empty = 0;
    for (int c = 0; c < m; c++) {
        int lst = -1;
        for (int r = 0; r < n; r++) {
            if (a[r][c] == -1) continue;
            if (lst != -1) {
                int dx = a[r][c] - a[lst][c];
                adj[lst].push_back({r, (dx + h) % h});
                adj[r].push_back({lst, (-dx + h) % h});
            }
            lst = r;
        }
        empty += (lst == -1);
    }
    vector<int> res(n, -1);
    int works = 1; // if there's a valid solution
    auto dfs = [&](int u, int t, auto&& dfs) -> void {
        res[u] = t;
        for (auto [v, w] : adj[u]) {
            int nt = (t + w) % h;
            if (res[v] == -1) {
                dfs(v, nt, dfs);
            } else if (nt != res[v]) {
                works = 0;
            }
        }
    };
    int comps = 0;
    for (int i = 0; i < n; i++) {
        if (res[i] == -1) dfs(i, 0, dfs), ++comps;
    }
    cout << expo(h, comps + empty - 1) * works << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Tick, Tock (CF)
 * We can determine relationships by looking at
 * two cells in the same column. Then, we can create
 * a weighted graph between the rows.
 * 
 * Note that, if there's an assigned value in some row,
 * then that column's value is also assigned. Also, some
 * rows might need to have reliant values. So, along with
 * these components (and the empty columns), we can binpow
 * to get our answer.
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