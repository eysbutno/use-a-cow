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
const int INF = 1e9;
void solve() {
    int p; cin >> p;
    if (p == 0) {
        cout << 0 << " " << 0 << "\n";
        return;
    }
    vector<int> dp(p + 1, INF);
    dp[0] = 0, dp[1] = 2; 
    auto pairs = [&](int cnt) -> ll {
        return (ll) cnt * (cnt - 1) / 2;
    };
    for (int i = 2; i <= p; i++) {
        for (int j = 2; j <= i; j++) {
            int add = pairs(j);
            if (add > i) break;
            smin(dp[i], j + dp[i - add]);
        }
    }
    cout << dp[p] << " " << pairs(dp[p]) - p << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Node Pairs (CF)
 * Problem Statement:
 * There are P pairs of nodes, such that 
 * u < v and u and v are reachable from another.
 * In other words, u and v are in the same SCC.
 * Then, you need to find the minimum # of nodes to
 * create a graph with P such pairs, and then find the
 * # of nodes. Each unidirectional pair of nodes will be two
 * nodes in different SCCs, where one node is in a SCC that has
 * an edge in the other one; you can count the # of these, by 
 * counting the # of options in the "top" SCC, * the # of nodes in the
 * "bottom" SCC. 
 * 
 * Anyways, note that in each SCC, there are N choose 2 pairs of nodes
 * that will be reachable from each other. So, you can just brute force
 * the size of each SCC added. All pairs of nodes that are not in the SCC,
 * will be unidirectional. So unidirectional nodes is just dp[p] * (dp[p] - 1) / 2 - p.
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