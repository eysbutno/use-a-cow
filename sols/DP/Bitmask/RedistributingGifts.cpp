#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 18;
int pref[N][N], con[N][N];
ll ans[1 << N], dp[1 << N][N];
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> pref[i][j];
            --pref[i][j];
        }
        for (int j = 0; j < n; j++) {
            con[i][pref[i][j]] = true;
            if (pref[i][j] == i) break;
        }
    }
    ans[0] = 1;
    for (int i = 1; i < (1 << n); i++) {
        int low = __builtin_ctz(i);
        dp[i][low] = ans[i ^ (1 << low)];
        for (int j = low; j < n; j++) {
            if (!(i >> j & 1)) continue;
            if (j != low) {
                for (int k = 0; k < n; k++) {
                    if ((i >> k & 1) && j != k && con[k][j]) {
                        dp[i][j] += dp[i ^ (1 << j)][k];
                    }
                }
            }
            if (con[j][low]) ans[i] += dp[i][j];
        }
    }
    int q; cin >> q;
    while (q--) {
        string state; cin >> state;
        int g = 0, h = 0;
        for (int i = 0; i < n; i++) {
            if (state[i] == 'G') g |= (1 << i);
            if (state[i] == 'H') h |= (1 << i);
        }
        cout << ans[g] * ans[h] << '\n';
    }
}
/**
 * TASK: Redistributing Gifts.
 * Observation 1: We can treat the Guernsey
 * and Holstein cows like separate groups, and
 * simply compute the answer if we can swap
 * between a given subset of cows.
 * 
 * Observation 2: If we draw an edge if cow
 * x prefers or is fine with gift y, then a 
 * reordering is only possible if you rotate
 * along a cycle.
 * 
 * Define dp[mask][last] to be the # of ways
 * to reach this state, where mask is the subset
 * of nodes that we can use the edges of, and
 * last is the current node of the cycle we're
 * building. Then, your state transition is just
 * dp[mask][last] += dp[mas ^ (1 << last)][prev], 
 * where prev is the previous source. Note that
 * you need to be very careful to not overcount.
*/