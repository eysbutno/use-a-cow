#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n, m; cin >> n >> m;
    vector a(n, vector(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    vector dp(n, vector(m, vector<int>()));
    dp[0][0] = {a[0][0]};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            sort(all(dp[i][j]));
            dp[i][j].erase(unique(all(dp[i][j])), 
                           end(dp[i][j]));
            vector<int> nw;
            for (int k = 0; k < sz(dp[i][j]); k++) {
                bool covered = false;
                for (int l = k + 1; l < sz(dp[i][j]); l++) {
                    if (dp[i][j][l] % dp[i][j][k] == 0) {
                        covered = true; break;
                    }
                }
                if (!covered) nw.push_back(dp[i][j][k]);
            }
            dp[i][j] = nw;
            for (int k : nw) {
                if (i + 1 < n) {
                    dp[i + 1][j].push_back(gcd(a[i + 1][j], k));
                }
                if (j + 1 < m) {
                    dp[i][j + 1].push_back(gcd(a[i][j + 1], k));
                }
            }
        }
    }
    cout << dp[n - 1][m - 1].back() << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: G. GCD on a Grid (CF)
 * DP[i][j][DIV] = if you can reach {i, j}, with
 * divisor DIV being maintained throughout. Then,
 * use push DP.
*/