#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct Edge {
    int r, f, s, t;
};
const ll LINF = 1e18;
void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<ll> x(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    vector<vector<Edge>> adj(n + 1);
    vector<set<int>> on(n + 1);
    for (int i = 0; i < k; i++) {
        int a, b, c, d, h;
        cin >> a >> b >> c 
            >> d >> h;
        adj[a].pb({b, c, d, h});
        on[a].ins(b);
        on[c].ins(d);
    }
    vector<map<int, ll>> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        for (int j : on[i]) {
            dp[i][j] = LINF;
        }
    }
    dp[1][1] = 0;
    dp[n][m] = LINF;
    on[1].ins(1);
    on[n].ins(m);
    for (int i = 1; i <= n; i++) {
        if (on[i].empty()) continue;
        vector<int> locs(all(on[i]));
        int sz = size(locs);
        for (int j = 1; j < sz; j++) {
            int l1 = locs[j], l2 = locs[j - 1];
            dp[i][locs[j]] = min(dp[i][l1], 
                dp[i][l2] + x[i] * (l1 - l2));
        }
        for (int j = sz - 2; j >= 0; j--) {
            int l1 = locs[j], l2 = locs[j + 1];
            dp[i][locs[j]] = min(dp[i][l1],
                dp[i][l2] + x[i] * (l2 - l1));
        }
        for (Edge& j : adj[i]) {
            if (dp[i][j.r] != LINF) {
                dp[j.f][j.s] = min(dp[j.f][j.s],
                    dp[i][j.r] - j.t);
            }
        }
    }
    if (dp[n][m] != LINF) {
        cout << dp[n][m];
    } else {
        cout << "NO ESCAPE";
    }
    cout << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Do DP by floor.
 * 
 * Room to room: Do a right to left,
 * and a left to right scan. Note that
 * you never strictly need to jump over
 * a series of rooms; going through adjacent
 * rooms over and over suffices.
 * 
 * Floor to floor: Just use the edges.
*/