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
    int n, m, k; 
    cin >> n >> m >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        char c; cin >> c;
        a[i] = c - 'a';
    }
    vector d(m, vector(m, 0));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            cin >> d[i][j];
        }
    }
    // calculates all-pairs-shortest-paths
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                smin(d[i][j], d[i][k] + d[k][j]);
                smin(d[j][i], d[j][k] + d[k][i]);
            }
        }
    }
    // prefix sums, to count cost to change a range.
    vector pf(n + 1, vector(m, 0));
    vector dp(n + 1, vector(m, INF));
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            pf[i][j] = pf[i - 1][j] + d[a[i]][j];
        }
    }
    // the DP stuff to get our answer.
    for (int i = 0; i < m; i++) {
        dp[k][i] = pf[k][i];
    }
    for (int i = k + 1; i <= n; i++) {
        int mn = INF;
        for (int j = 0; j < m; j++) {
            smin(mn, dp[i - k][j]);
        }
        for (int j = 0; j < m; j++) {
            // Case 1: Have a completely new streak.
            smin(dp[i][j], pf[i][j] - pf[i - k][j] + mn);
            // Case 2: Add to an existing streak.
            smin(dp[i][j], d[a[i]][j] + dp[i - 1][j]);
        }
    }
    int res = INF;
    for (int i = 0; i < m; i++) {
        smin(res, dp[n][i]);
    }
    cout << res << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Moortal Cowmbat (Gold)
 * At any time, you can either:
 * 1. Add a new character to a previous streak.
 * 2. Create a brand new streak of minimum length k.
 * This motivates our DP states and our DP state transitions.
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