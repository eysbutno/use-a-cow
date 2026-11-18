#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll dp[5000][5000];
const int MX = 1e6;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("threesum.in", "r", stdin);
    freopen("threesum.out", "w", stdout);
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i], a[i] += MX;
    }
    vector<int> freq(MX * 2 + 1);
    auto query = [&](int l, int r) {
        int t = MX * 3 - a[l] - a[r];
        if (t >= 0 && t <= MX * 2) {
            return freq[t];
        }
        return 0;
    };
    for (int l = n - 3; l >= 0; l--) {
        freq[a[l + 1]]++;
        for (int r = l + 2; r < n; r++) {
            dp[l][r] = dp[l + 1][r] + dp[l][r - 1]
                     - dp[l + 1][r - 1] + query(l, r);
            freq[a[r]]++;
        }
        for (int r = l + 1; r < n; r++) {
            freq[a[r]]--;
        }
    }
    while (q--) {
        int x, y; cin >> x >> y;
        cout << dp[--x][--y] << '\n';
    }
}
/**
 * TASK: 3SUM.
 * The way you can calculate a dp[i][j]
 * is by the following: 
 * dp[i][j] = dp[i + 1][j] + dp[i][j - 1]
 *          - dp[i - 1][j - 1] + ways[i][j].
 * ways[i][j] denotes the # of triplets you
 * can form with i and j as the endpoints.
 * 
 * Kind of like PIE. Excludes L + Excludes R
 * minus Excludes L & R + Results with L and
 * R included in the result.
*/