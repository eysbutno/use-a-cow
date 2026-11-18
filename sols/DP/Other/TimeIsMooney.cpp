#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int D = 1e3, N = 1e3;
vector<int> adj[N];
int dp[D + 1][N], p[N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
    int n, m, c; 
    cin >> n >> m >> c;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y; 
        cin >> x >> y;
        --x, --y;
        adj[x].pb(y);
    }
    for (int i = 0; i <= D; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    int res = 0;
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < n; j++) {
            if (dp[i][j] == -1) continue;
            for (int k : adj[j]) {
                dp[i + 1][k] = max(
                    dp[i + 1][k], dp[i][j] + p[k]
                );
            }
        }
        res = max(res, dp[i][0] - c * i * i);
    }
    cout << res << '\n';
}
/**
 * dp[i][j] = max money on day i, 
 * ending in city j.
 * 
 * Most days possible is 1000 due to
 * 1000^2 * c >= any amt of profit
*/