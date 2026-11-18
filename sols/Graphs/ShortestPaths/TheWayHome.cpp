#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;
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
const ll INF = 1e18;
void solve() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<ll> w(n);
    for (ll &i : w) {
        cin >> i;
    }
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y, w; cin >> x >> y >> w;
        adj[--x].push_back({--y, w});
    }
    const pll DEF = {INF, INF};
    vector dp(n, vector(n, DEF));
    // {perfs, -$$$s}, so you can just min()
    priority_queue<pair<pll, pll>> pq;
    pq.push({{0, p}, {0, 0}});
    // {-perfs, $$$s}, {u, v}.
    dp[0][0] = {0, -p};
    while (!pq.empty()) {
        auto [_, __] = pq.top(); pq.pop();
        auto [pfs, mon] = _;
        auto [u, v] = __;
        if (dp[u][v] != make_pair(-pfs, -mon)) {
            continue;
        }
        pfs *= -1; // to revert negative number
        for (auto [nxt, cost] : adj[u]) {
            int bst = w[nxt] > w[v] ? nxt : v;
            pll prop = DEF; // the next "transition" val
            if (mon >= cost) { // can just buy ticket it right now
                prop = {pfs, cost - mon}; // 2nd val is negative
            } else { // must perform, zoinks
                ll divs = (cost - mon + w[v] - 1) / w[v];
                prop = {pfs + divs, cost - mon - divs * w[v]};
            }  
            if (smin(dp[nxt][bst], prop)) {
                pq.push({{-prop.f, -prop.s}, {nxt, bst}});
            }
        }
    }
    ll res = INF;
    for (int i = 0; i < n; i++) {
        smin(res, dp[n - 1][i].f);
    }
    cout << (res < INF ? res : -1) << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: The Way Home (CF).
 * Observation 1: It is always optimal to
 * pre-earn money from the most profitable location.
 * 
 * Let dp[u][v] be {min perfs, current $$$}, to get to
 * node u while v is the best on path. Then,
 * use Dijkstra to calculate the DP array. 
 * It is easy to prove that minimizing the quantity
 * {min perfs, -$$$s current} is always optimal, for
 * a given "best" pre-buying node.
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