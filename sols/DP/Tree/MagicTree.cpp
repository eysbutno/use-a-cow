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
    int n, m, k; cin >> n >> m >> k;
    vector f(n, array<int, 2>{-1, -1});
    vector<int> p(n);
    for (int i = 1; i < n; i++) {
        int x; cin >> x;
        p[i] = --x;
    }
    for (int i = 0; i < m; i++) {
        int v, d, w;
        cin >> v >> d >> w;
        f[--v] = {d, w};
    }
    vector dp(n, map<ll, ll>());
    for (int i = n - 1; i >= 0; i--) {
        // adding this current fruit into differences
        if (f[i] != array<int, 2>{-1, -1}) {
            // difference added is initially w_i.
            dp[i][f[i][0]] += f[i][1];
            auto it = dp[i].upper_bound(f[i][0]);
            while (it != end(dp[i])) {
                if (it -> s > f[i][1]) {
                    it -> s -= f[i][1];
                    break;
                }
                f[i][1] -= it -> s;
                auto prv = it; ++it;
                dp[i].erase(prv);
            }
        }
        // merging the subtree answers
        if (sz(dp[i]) > sz(dp[p[i]])) {
            swap(dp[i], dp[p[i]]);
        }
        for (auto [k, v] : dp[i]) {
            dp[p[i]][k] += v;
        }
    }
    ll res = 0;
    for (auto [k, v] : dp[0]) {
        res += v;
    }
    cout << (res >> 1) << '\n';
}
/**
 * TASK: B. Magic Tree (CEOI)
 * Note the following constraints: 
 * - When you cut a subtree, it IMMEDIATELY falls.
 * - That means to cut off an arbitrary subtree,
 *   any cuts that happened beforehand within this 
 *   subtree must have had t_prev < t_cur.
 * 
 * Let dp[i][j] be the result, for max juice you can
 * harvest, from the subtree of i in the first j days.
 * This initial idea takes O(NK) time and space.
 * 
 * Optimization Main Idea: Keep a map of all nonzero
 * dp[i][j] - dp[i][j - 1], for each day value. For 
 * each subtree, we initially small to large merge the 
 * children. When adding in each root, we account for
 * the fact that any current time AFTER d_i cannot include
 * anything related to the root.
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