#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

ll dp[100][8];
const ll LINF = 1e18;
void reset() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 8; j++) {
            dp[i][j] = LINF;
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
    int n, k; 
    cin >> n >> k;
    vector<int> a(n);
    ll res = LINF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto solve = [&](vector<int>& mix) {
        ll best = LINF;
        vector<ll> suffix(n);
        suffix[n - 1] = mix.back();
        for (int i = n - 2; i >= 0; i--) {
            suffix[i] = mix[i] + suffix[i + 1];
        }
        for (int i = 2; i <= k; i++) {
            // i doors placed
            for (int j = 0; j < n; j++) {
                for (int l = j + 1; l < n; l++) {
                    ll saved = (ll) (l - j) * suffix[l];
                    ckmin(dp[l][i], dp[j][i - 1] - saved);
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 1; j <= k; j++) {
                ckmin(best, dp[i][j]);
            }
        }
        return best;
    };
    for (int i = 0; i < n; i++) {
        reset();
        vector<int> mix = {a[i]};
        for (int j = (i + 1) % n; j != i; 
            j = (j + 1) % n) {
            mix.pb(a[j]);
        }
        dp[0][1] = 0;
        for (int j = 1; j < n; j++) {
            dp[0][1] += mix[j] * j;
        }
        ckmin(res, solve(mix));
    }
    cout << res << '\n';
}
/**
 * Brute force the starting barn. Define
 * dp[i][j] to be best result if the
 * j'th door is placed at index i.
*/