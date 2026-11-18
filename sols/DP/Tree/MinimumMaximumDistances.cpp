#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 2e5 + 1;
vector<int> adj[MAX];
bool isMarked[MAX];
int f[MAX], s[MAX], c[MAX];
void dfs1(int node, int prev) {
    for (int i : adj[node]) {
        if (i != prev) {
            dfs1(i, node);
            int dist = f[i];
            if (dist) ++dist;
            if (isMarked[i]) {
                dist = max(dist, 1);
            }
            if (dist > f[node]) {
                s[node] = f[node];
                f[node] = dist;
                c[node] = i;
            } else if (dist > s[node]) {
                s[node] = dist;
            }
        }
    }
}
void dfs2(int node, int prev) {
    if (node != 1) {
        int dist = 0;
        if (c[prev] != node) {
            dist = f[prev];
        } else {
            dist = s[prev];
        }
        if (dist) ++dist;
        if (isMarked[prev]) {
            dist = max(dist, 1);
        }
        if (dist > f[node]) {
            s[node] = f[node];
            f[node] = dist;
            c[node] = -1;
        } else if (dist > s[node]) {
            s[node] = dist;
        }
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dfs2(i, node);
        }
    }
}
void solve() {
    int n, k; cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        isMarked[i] = 0;
        f[i] = 0;
        s[i] = 0;
        c[i] = 0;
    }
    for (int i = 0; i < k; i++) {
        int a; cin >> a;
        isMarked[a] = 1;
    }
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    dfs1(1, -1);
    dfs2(1, -1);
    int mn = 2e9;
    for (int i = 1; i <= n; i++) {
        mn = min(mn, f[i]);
    }
    cout << mn << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Tree Distances 1, but with
 * modified distance formulas.
*/