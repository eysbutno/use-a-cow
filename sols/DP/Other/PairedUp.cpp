#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define mp(x, y) make_pair(x, y)
#define pb push_back
#define ins insert
#define f first
#define s second

int t, n, k;
const int INF = 2e9;
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int s1(vector<pii>& active) {
    if (sz(active) % 2 == 0) {
        return 0;
    }
    int mn = INT_MAX, z = sz(active);
    auto notEnds = [&](int i) {
        return i != 0 && i != z - 1;
    };
    auto canBridge = [&](int i) {
        return notEnds(i) && active[i + 1].f
            - active[i - 1].f <= k;
    };
    for (int i = 0; i < z; i++) {
        if (canBridge(i) || !(i & 1)) {
            smin(mn, active[i].s);
        }
    }
    return mn;
}
int s2(vector<pii>& active) {
    int z = sz(active);
    if (!z) return 0;
    vector<vector<int>> dp(2, vector<int>(z + 1));
    auto notEnds = [&](int i) {
        return i != 0 && i != z - 1;
    };
    auto canBridge = [&](int i) {
        return notEnds(i) && (active[i + 1].f
            - active[i - 1].f <= k);
    };
    dp[1][z] = -INF;
    for (int i = z - 1; i >= 0; i--) {
        dp[0][i] = dp[0][i + 1];
        dp[1][i] = dp[1][i + 1];
        int b = upper_bound(all(active), 
            mp(active[i].f + k, INF)) - begin(active);
        if (!notEnds(i) || canBridge(i) || !(z - i & 1)) {
            smax(dp[0][i], dp[1][b] + active[i].s);
        }
        if (!notEnds(i) || canBridge(i) || (z - i & 1)) {
            smax(dp[1][i], dp[0][b] + active[i].s);
        }
    }
    return dp[z % 2][0];
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> t >> n >> k;
    int prev = -1, res = 0;
    vector<pii> active;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        if (x - prev > k) {
            if (t == 1) res += s1(active);
            else res += s2(active);
            active.clear();
        }
        active.pb({x, y});
        prev = x;
    }
    cout << res + (t < 2 ? s1(active) : s2(active));
}
/**
 * Maximization problem, so DP.
 * If two cows can be paired up, then 
 * draw an imaginary line between them.
 * Define a "chain" to be a sequence of
 * repeated lines. 
 * 
 * Case 1: T = 1 (Minimum)
 * For all even length chains, you can pair
 * up everything. Otherwise, leave the minimum
 * cow unpaired.
 * 
 * Case 2: T = 2 (Maximum)
 * Try to break up as many chains as possible,
 * leaving some elements unpaired. For each cow i,
 * maintain the following state transitions:
 * dp[0][i] = max result, if an even amount of
 * cows are paired up.
 * dp[1][i] = max result, if an odd amount of cows
 * are paired up.
 * Make dp[0][i] and dp[1][i] be correct if the #
 * of cows in the chain are of the same parity. The
 * answer does not need to be the same if this is 
 * not the case.
 * 
 * Therefore, dp[s][i] = max(dp[s][i + 1], dp[!s][ub[i]] + y_i).
 * ub[i] is equal to the leftmost cow that can be left
 * unpaired if i is also unpaired.
*/