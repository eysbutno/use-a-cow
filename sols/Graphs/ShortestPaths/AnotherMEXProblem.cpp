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
    int n; cin >> n;
    vector a(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    vector nxt(n + 2, vector(n + 1, n + 1));
    for (int i = 1; i <= n; i++) {
        vector<bool> seen(n + 2);
        int ptr = 0; // current MEX.
        for (int j = i; j <= n; j++) {
            seen[a[j]] = true;
            while (seen[ptr]) ++ptr;
            if (nxt[ptr][i] > n) {
                nxt[ptr][i] = j;
            }
        }
    }
    for (int i = 0; i <= n + 1; i++) {
        for (int j = n - 1; j >= 1; j--) {
            smin(nxt[i][j], nxt[i][j + 1]);
        }
    }
    vector dp(n * 2 + 1, INF);
    vector vis(n * 2 + 1, false);
    dp[0] = 0; // 0 mex = [] array.
    for (int t = 0; t <= n * 2; t++) {
        // n * 2 nodes, in total.
        int v = -1; // currently no option
        for (int i = 0; i <= n * 2; i++) {
            if (!vis[i] && (v == -1 || dp[i] < dp[v])) {
                v = i;
            }
        }
        if (v < 0 || dp[v] >= n) break;
        // we cannot progress any more.
        for (int i = 0; i <= n + 1; i++) {
            // i is the MEX transition value.
            int r = nxt[i][dp[v] + 1];
            if (r <= n) smin(dp[v ^ i], r);
        }
        vis[v] = true; // so idx isn't revisited
    }
    for (int i = n * 2; i >= 0; i--) {
        if (dp[i] <= n) {
            cout << i << "\n";
            return;
        }
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Another MEX Problem.
 * Observation 1: For each MEX XOR value,
 * we want the prefix of subarrays used
 * to be minimized.
 * 
 * Proof: Smaller prefix -> you can use more
 * subarrays later on.
 * 
 * With this observation, and a bit of precalculation,
 * you can use Dijkstra's to solve this problem.
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