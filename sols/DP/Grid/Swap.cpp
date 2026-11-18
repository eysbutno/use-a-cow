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
    string s; cin >> s;
    int n = s.length();
    int k; cin >> k;
    smin(k, n * (n + 1) / 2);
    map<string, map<int, ll>> dp;
    auto memo = [&](string cur, int edits, 
                    auto&& memo) -> ll {
        int z = cur.length();
        if (edits < 0) return 0;
        if (z <= 1 || edits == 0) {
            return 1;
        }
        if (dp[cur][edits] != 0) {
            return dp[cur][edits];
        }
        ll &res = dp[cur][edits];
        for (char c : "KEY") {
            for (int i = 0; i < z; i++) {
                if (cur[i] != c) continue;
                string nxt = cur.substr(0, i) 
                           + cur.substr(i + 1);
                res += memo(nxt, edits - i, memo);
                break;
            }
        }
        return res;
    }; cout << memo(s, k, memo) << "\n";
}
/**
 * TASK: E - Swap (AtCoder)
 * Strategy: For every string and k pair, 
 * memoize it. To properly count everything,
 * do the following:
 * 
 * For each possible character, take the first
 * occurence of it. Note that, we can swap this
 * character with any other one in the string before.
 * So we add dp(string if excluding this, edits - possible swaps).
 * Or something to that effect.
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