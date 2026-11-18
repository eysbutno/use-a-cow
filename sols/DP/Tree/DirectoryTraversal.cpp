#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5;
vector<int> adj[N];
int subFiles[N], len[N];
ll dp[N], tot;
bool isFile[N];
void dfs1(int u, int p) {
    for (int i : adj[u]) {
        if (i == p) continue;
        if (isFile[i]) {
            ++subFiles[u];
        } else {
            dfs1(i, u);
            dp[u] += dp[i] + (ll) (len[i] + 1) 
                * subFiles[i];
            subFiles[u] += subFiles[i];
        }
    }
}
void dfs2(int u, int p) {
    for (int i : adj[u]) {
        if (i == p) continue;
        if (!isFile[i]) {
            ll other = subFiles[0] - subFiles[i];
            dp[i] = dp[u] + other * 3 - (ll) 
                (len[i] + 1) * subFiles[i];
            dfs2(i, u);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("dirtraverse.in", "r", stdin);
    freopen("dirtraverse.out", "w", stdout);
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        len[i] = s.length();
        int m; cin >> m;
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            adj[i].pb(--x);
            adj[x].pb(i);
        }
        if (m == 0) {
            tot += len[i];
            isFile[i] = true;
        }
    }
    dfs1(0, -1), dfs2(0, -1);
    ll res = INT64_MAX;
    for (int i = 0; i < n; i++) {
        if (!isFile[i]) {
            ckmin(res, dp[i]);
        }
    }
    cout << res + tot << '\n';
}
/**
 * Problem: Directory Traversal.
 * Note: Graph is a tree, where
 * each edge has a variable weight
 * If going upwards, it's a weight of
 * 3. If going downwards, it's the weight
 * of the current node's string length.
 * Do some funny Tree DP/Rerooting to
 * get your final result.
*/