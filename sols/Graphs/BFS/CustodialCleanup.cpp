#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n, m; cin >> n >> m;
    vector<int> c(n), s(n), f(n);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i], --c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i], --s[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> f[i], --f[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[--x].pb(--y);
        adj[y].pb(x);
    }
    vector<vector<bool>> vis(2, vector<bool>(n));
    for (int t = 0; t < 2; t++) {
        vector<vector<int>> wait(n);
        queue<int> q({0});
        set<int> active;
        vector<bool> tmp(n);
        tmp[0] = true;
        active.ins(s[0]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            vis[t][u] = true;
            for (int i : adj[u]) {
                if (tmp[i]) continue;
                if (t && !vis[0][i]) continue;
                tmp[i] = true;
                if ((t && c[i] == s[i]) ||
                    active.count(c[i])) {
                    q.push(i);
                } else {
                    wait[c[i]].pb(i);
                }
            }
            active.ins(s[u]);
            for (int i : wait[s[u]]) {
                q.push(i);
            }
            wait[s[u]].clear();
        }
        swap(f, s);
    }
    for (int i = 0; i < n; i++) {
        if ((vis[0][i] && !vis[1][i]) ||
            (!vis[0][i] && s[i] != f[i])) {
            cout << "NO" << '\n';
            return;
        }
    }
    cout << "YES" << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Custodial Cleanup
 * 1. The optimal strategy is to get
 * all the keys, and then return them
 * one by one.
 * 
 * 2. If we know you can get every key,
 * then set s[i] to be f[i]. Another way
 * to view this is you needing c[i] to 
 * exit.
*/