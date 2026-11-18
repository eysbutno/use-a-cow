#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define mp(a, b) make_pair(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

ll dp[1001][1001][2];
int dist(pii a, pii b) {
    int dx = a.f - b.f,
        dy = a.s - b.s;
    return dx * dx + dy * dy;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("checklist.in", "r", stdin);
    freopen("checklist.out", "w", stdout);
    int h, g; cin >> h >> g;
    vector<pii> ch(h + 1), cg(g + 1);
    for (int i = 1; i <= h; i++) {
        int x, y; cin >> x >> y;
        ch[i] = mp(x, y);
    }
    for (int i = 1; i <= g; i++) {
        int x, y; cin >> x >> y;
        cg[i] = mp(x, y);
    }
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= g; j++) {
            for (int k = 0; k < 2; k++) {
                dp[i][j][k] = 1e18;
            }
        }
    }
    dp[1][0][0] = 0;
    for (int i = 0; i <= h; i++) {
        for (int j = 0; j <= g; j++) {
            if (i > 1) {
                smin(dp[i][j][0], dp[i - 1][j][0] 
                    + dist(ch[i - 1], ch[i]));
            }
            if (j > 1) {
                smin(dp[i][j][1], dp[i][j - 1][1] 
                    + dist(cg[j - 1], cg[j]));
            }
            if (i > 0 && j > 0) {
                smin(dp[i][j][0], dp[i - 1][j][1] 
                    + dist(ch[i], cg[j]));
                smin(dp[i][j][1], dp[i][j - 1][0] 
                    + dist(ch[i], cg[j]));
            }
        }   
    }
    cout << dp[h][g][0] << "\n";
}
/**
 * TASK: Cow Checklist.
 * dp[i][j] = distance required
 * to visit the first i G's and 
 * first j H's.
 * 
 * dp[i][j] = min(dp[i - 1][j] + d_i,
 *                dp[i][j - 1] + d_j)
 * Make sure to keep another parameter 
 * to see if the last cow visited was a 
 * G or a H. 1 for G, 0 for H.
*/