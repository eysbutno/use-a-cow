#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back 

const int N = 300'001;
const ll INF = 1e18;
vector<pii> adj[N];
ll d[N], dp[2][N];
void dfs(int u, int p) {
    int cnt = d[u];
    vector<ll> dx;
    for (auto [i, w] : adj[u]) {
        if (i != p) {
            dfs(i, u);
            ll v1 = dp[0][i],
                v2 = dp[1][i];
            dp[0][u] += v2;
            dp[1][u] += v2;
            if (d[i] > 0) {
                dx.pb(w + v1 - v2);
            }
        }
    }
    sort(all(dx), greater<ll>());
    for (int i = 0; i < sz(dx); i++) {
        if (i >= d[u] || dx[i] < 0) {
            break;
        }
        if (i < d[u] - 1) {
            dp[0][u] += dx[i];
            dp[1][u] += dx[i];
        } else {
            dp[1][u] += dx[i];
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> d[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({y, w});
        adj[y].pb({x, w});
    }
    dfs(1, 0);
    cout << dp[1][1];
}
/**
 * Two DP states: if you can
 * connect this node to the
 * parent, and if you can't.
*/