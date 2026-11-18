#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5 + 1;
vector<int> adj[N];
vector<ll> pf[N], sf[N];
ll n, m, dp[N], dp2[N];
void dfs1(int node, int prev) {
    dp[node] = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            dfs1(i, node);
            dp[node] *= (dp[i] + 1);
            dp[node] %= m;
        }
    }
    int x = sz(adj[node]);
    pf[node] = vector<ll>(x + 2, 1);
    sf[node] = vector<ll>(x + 2, 1);
    for (int i = 1; i <= x; i++) {
        int u = adj[node][i - 1];
        pf[node][i] = pf[node][i - 1];
        if (u == prev) continue;
        pf[node][i] *= (dp[u] + 1);
        pf[node][i] %= m;
    }
    for (int i = x; i >= 1; i--) {
        sf[node][i] = sf[node][i + 1];
        int u = adj[node][i - 1];
        if (u == prev) continue;
        sf[node][i] *= (dp[u] + 1);
        sf[node][i] %= m;
    }
}
void dfs2(int node, int prev) {
    int x = sz(adj[node]);
    for (int i = 1; i <= x; i++) {
        int u = adj[node][i - 1];
        if (u == prev) continue;
        dp2[u] = ((dp2[node] * pf[node][i - 1]) % m
            * sf[node][i + 1] + 1) % m;
        dfs2(u, node);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb(y), adj[y].pb(x);
    }
    dp2[1] = 1;
    dfs1(1, 0), dfs2(1, 0);
    for (int i = 1; i <= n; i++) {
        cout << (dp[i] * dp2[i]) % m << '\n';
    }
}
/**
 * TASK: Subtree.
 * Calculate dp[i] = the number
 * of ways to handle all the
 * nodes in node i's subtree,
 * and dp2[i] to handle every
 * node not in the subtree. The 
 * answer is (dp[i] * dp2[i]) % m.
*/