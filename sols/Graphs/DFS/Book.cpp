#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 2e5;
vector<int> adj[N];
vector<int> topsort;
bool vis[N];
int dp[N];
void dfs(int node) {
    vis[node] = true;
    for (int i : adj[node]) {
        if (!vis[i]) dfs(i);
    }
    topsort.pb(node);
}
void compute(int n) {
    for (int i = 0; i < n; i++) {
        if (!vis[i]) dfs(i);
    }
    reverse(all(topsort));
}
void dfs2(int node) {
    vis[node] = true;
    for (int i : adj[node]) {
        if (!vis[i]) dfs2(i);
        ckmax(dp[node], dp[i] + (node < i));
    }
}
void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        vis[i] = false;
        dp[i] = 0;
        int k; cin >> k;
        for (int j = 0; j < k; j++) {
            int a; cin >> a;
            adj[i].pb(--a);
        }
    }
    topsort.clear();
    compute(n);
    vector<int> ind(n);
    for (int i = 0; i < n; i++) {
        ind[topsort[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (ind[j] <= ind[i]) {
                cout << -1 << '\n';
                return;
            }
        }
    }
    fill(vis, vis + n, false);
    for (int i : topsort) {
        if (!vis[i]) dfs2(i);
    }
    int mx = 0;
    for (int i = 0; i < n; i++) {
        ckmax(mx, dp[i]);
    }
    cout << mx + 1 << '\n';
} 
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Books.
 * Observations:
 * 1. You can construct a graph,
 * with an edge from chapter A to B,
 * if you need to read chapter B to
 * understand chapter A. It'll have a 
 * weight of 1 if A < B, and 0 otherwise.
 * 2. This graph must be acyclic,
 * otherwise it's impossible.
 * 3. Each path is independent from each
 * other, so the answer is the longest 
 * (weighted) path, plus one.
 * 
 * Use toposort to solve this problem,
 * then use some very simple DP.
*/