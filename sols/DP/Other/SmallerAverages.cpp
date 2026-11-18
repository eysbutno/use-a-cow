#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

constexpr int MOD = 1e9 + 7;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> pa(n + 1), pb(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> pa[i], pa[i] += pa[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        cin >> pb[i], pb[i] += pb[i - 1];
    }
    /** @return a / b < c / d, or a / b <= c / d if eq = true */
    auto cmp = [](int a, int b, int c, int d, bool eq = false) -> bool {
        if (eq) return 1ll * a * d <= 1ll * b * c;
        return 1ll * a * d < 1ll * b * c;
    };
    vector<vector<int>> orda(n + 1), ordb(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            orda[i].push_back(j);
            ordb[i].push_back(j);
        }
        // sorting all the subarrays by their average
        sort(all(orda[i]), [&](int x, int y) {
            return cmp(pa[i] - pa[x], i - x, pa[i] - pa[y], i - y);
        });
        sort(all(ordb[i]), [&](int x, int y) {
            return cmp(pb[i] - pb[x], i - x, pb[i] - pb[y], i - y);
        });
    }
    // dp[i][j] = ways, if we are at idx i in arr a and j in arr b
    vector dp(n + 1, vector<int>(n + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        vector<int> &oa = orda[i];
        vector cs(i, vector(n + 1, 0));
        // col sum [i lowest averages][value of j]
        for (int j = 0; j < i; j++) {
            for (int k = 0; k <= n; k++) {
                cs[j][k] = ((j ? cs[j - 1][k] : 0) + dp[oa[j]][k]) % MOD;
            }
        }
        // calculating dp[i][j]
        for (int j = 1; j <= n; j++) {
            vector<int> &ob = ordb[j];
            int ptr = 0;
            for (int k : ob) {
                // finding max k, such that there are k subarrays ending at i <= [j, k]'s average
                while (ptr < i && cmp(pa[i] - pa[oa[ptr]], i - oa[ptr], pb[j] - pb[k], j - k, true))
                    ++ptr;
                (dp[i][j] += (ptr ? cs[ptr - 1][k] : 0)) %= MOD;
            }
        }
    }
    cout << dp[n][n] << "\n";
}