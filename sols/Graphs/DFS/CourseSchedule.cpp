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

const int N = 1e5;
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
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[--a].pb(--b);
    }
    compute(n);
    vector<int> ind(n);
    for (int i = 0; i < n; i++) {
        ind[topsort[i]] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j : adj[i]) {
            if (ind[j] <= ind[i]) {
                cout << "IMPOSSIBLE" << '\n';
                return 0;
            }
        }
    }
    for (int i : topsort) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}