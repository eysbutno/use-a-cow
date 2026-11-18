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

int dp[5001][5001][2];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> c;
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        if (c.empty() || v != c.back()) {
            c.pb(v);
        }
    }
    n = sz(c);
    for (int d = 1; d < n; d++) {
        for (int l = 0; l + d < n; l++) {
            int r = l + d;
            dp[l][r][0] = min(
                dp[l + 1][r][0] + (c[l] != c[l + 1]),
                dp[l + 1][r][1] + (c[l] != c[r])
            );
            dp[l][r][1] = min(
                dp[l][r - 1][0] + (c[r] != c[l]),
                dp[l][r - 1][1] + (c[r] != c[r - 1])
            );
        }
    }
    cout << min(dp[0][n - 1][0], dp[0][n - 1][1]);
}
/**
 * TASK: Flood Fill (CF).
 * Observation 1: When we start from a location,
 * eventually the borders will become one contiguous
 * array.
 * 
 * Observation 2: The only state we need to represent
 * a position with is the two endpoints, and which
 * endpoint's color we use.
 * Reasoning: We reason that [l, r] should be filled in
 * if we're expanding, and that it MUST be one of those
 * two colors.
*/