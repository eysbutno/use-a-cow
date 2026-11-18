#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 401;
const int INF = 1e9;
int dp[MAX][MAX];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
    int n, k; 
    cin >> n >> k;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    int mx = 0, sum = 0;
    for (int i = 0; i < n; i++) {
        mx = max(mx, a[i]);
        sum += a[i];
        dp[i][0] = mx * (i + 1) - sum;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= k; j++) {
            dp[i][j] = INF;
        }
    }
    for (int i = 1; i < n; i++) {
        // starting a grouping at i
        for (int j = 1; j <= k; j++) {
            // using j net changes
            int prev = dp[i - 1][j - 1],
                mx = 0, sum = 0;
            for (int l = i; l < n; l++) {
                mx = max(mx, a[l]);
                sum += a[l];
                dp[l][j] = min(dp[l][j], prev + 
                    mx * (l - i + 1) - sum);
            }
        }
    }
    cout << dp[n - 1][k] << '\n';
}