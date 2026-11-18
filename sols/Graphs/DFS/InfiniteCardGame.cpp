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
    vector<array<int, 2>> a(n);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[j][i];
        }
    }
    int m; cin >> m;
    vector<array<int, 2>> b(m);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < m; j++) {
            cin >> b[j][i];
        }
    }
    // array<int, 2> = {attk, def}.
    sort(all(a)), sort(all(b));
    vector<int> sf1(n + 1), sf2(m + 1);
    for (int i = n - 1; i >= 0; i--) {
        sf1[i] = max(sf1[i + 1], a[i][1]);
    }
    for (int i = m - 1; i >= 0; i--) {
        sf2[i] = max(sf2[i + 1], b[i][1]);
    }
    int mx1 = a.back()[0], mx2 = b.back()[0];
    map<pii, int> memo;
    auto dfs = [&](int id, int def, auto&& dfs) -> int {
        if (def >= (id > 0 ? mx1 : mx2)) {
            return id; // winner
        }
        pii cur = {id, def};
        if (memo.count(cur)) {
            return memo[cur];
        }
        memo[cur] = 0; // for ties
        int best = -1; // set later
        array<int, 2> arr = {def + 1, -1};
        if (id > 0) {
            int idx = lower_bound(all(a), arr)
                    - begin(a);
            best = sf1[idx];
        } else {
            int idx = lower_bound(all(b), arr)
                    - begin(b);
            best = sf2[idx];
        }
        return memo[cur] = dfs(-id, best, dfs);
    };
    vector<int> res(3);
    for (int i = 0; i < n; i++) {
        res[dfs(-1, a[i][1], dfs) + 1]++;
    }
    for (int i : res) {
        cout << i << ' ';
    }
    cout << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Infinite Card Game.
 * Observation 1: We only care about the
 * most recently played card, and it's defense.
 * 
 * Observation 2: For each card, we only need to
 * consider the card with highest defense, that can
 * still beat this current card.
 * 
 * Based on these observations, you can DFS on 
 * the player #, and the defense of the card.
 * NOTE: You don't need to care about the card
 * # that each player plays, cuz it's irrelevant.
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