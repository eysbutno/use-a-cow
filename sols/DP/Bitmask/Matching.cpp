#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 21;
const int MOD = 1e9 + 7;
int dp[1 << N];
bool ok[N][N];
int main() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ok[i][j];
        }
    }
    dp[0] = 1;
    for (int i = 0; i < (1 << n); i++) {
        int pairs = __builtin_popcount(i);
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) || !ok[pairs][j]) {
                continue;
            }
            dp[i | (1 << j)] += dp[i];
            dp[i | (1 << j)] %= MOD;
        }
    }
    cout << dp[(1 << n) - 1] << '\n';
}
/**
 * Algorithm:
 * Use Bitmask DP. Maintain dp[S] 
 * to be the number of pairings for
 * the subset of women S, to the 
 * first |s| males. Then, the DP
 * state transition is just to do
 * push DP on all compatible women.
*/