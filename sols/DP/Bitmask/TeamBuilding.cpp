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

const ll INF = 1e18;
ll dp[100'001][1 << 7],
   str[100'001][7];
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, p, k; cin >> n >> p >> k;
    vector<int> a(n + 1), ord(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            cin >> str[i][j];
        }
    }
    iota(all(ord), 0);
    sort(begin(ord) + 1, end(ord), 
        [&](int x, int y) {
        return a[x] > a[y];
    });
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < (1 << p); j++) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        int idx = ord[i];
        for (int j = 0; j < (1 << p); j++) {
            // case 1: add to audience
            dp[i][j] = dp[i - 1][j];
            int used = i - 1 - __builtin_popcount(j);
            if (used < k) dp[i][j] += a[idx];
            // case 2: add to team
            for (int b = 0; b < p; b++) {
                int bit = 1 << b;
                if (j & bit) {
                    smax(dp[i][j], dp[i - 1][j - bit] + str[idx][b]);
                }
            }
        }
    }
    cout << dp[n][(1 << p) - 1];
}
/**
 * Main idea: Use bitmasks for players
 * in each position, and use DP.
 * 
 * Implementation Notes: 
 * - One index to make your life easier
 * - Most important: Sort indexes by a_i!
 *   This allows you to, for every mask, know
 *   how many people have been put as audience,
 *   because if you CAN take an audience player 
 *   with your current mask, it's optimal to.
 * 
 * NOTE: We use bitmask DP to replace "expensive"
 * combinatorics with "clean" bitmask operations.
*/