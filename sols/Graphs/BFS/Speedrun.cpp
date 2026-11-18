#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n, m, k; 
    cin >> n >> m >> k;
    vector<int> h(n), deg(n);
    for (int& i : h) {
        cin >> i;
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[--x].pb(--y);
        deg[y]++;
    }
    queue<int> q;
    vector<int> st, t(n);
    for (int i = 0; i < n; i++) {
        if (!deg[i]) q.push(i), st.pb(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int i : adj[u]) {
            t[i] = max(t[i], t[u] + (h[i] < h[u]));
            if (--deg[i] == 0) q.push(i);
        }
    }
    sort(all(st), [&](int x, int y) {
        return h[x] < h[y];
    });
    ll worst = 0;
    for (int i = 0; i < n; i++) {
        worst = max(worst, (ll) t[i] * k + h[i]);
    }
    auto dfs = [&](int u, auto&& dfs) -> void {
        worst = max(worst, (ll) t[u] * k + h[u]);
        for (int i : adj[u]) {
            if (t[u] + (h[i] < h[u]) > t[i]) {
                t[i] = t[u] + (h[i] < h[u]);
                dfs(i, dfs);
            }
        }
    };
    ll res = worst - h[st[0]];
    for (int i = 1; i < sz(st); i++) {
        t[st[i - 1]] = 1, dfs(st[i - 1], dfs);
        res = min(res, worst - h[st[i]]);
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
/**
 * TASK: Speedrun (CF).
 * First, consider all the starting
 * times when starting time x = 0.
 * Then, construct the optimal ending
 * times when x = 0.
 * 
 * All the possible other starting time
 * candidates are a value of h[v], where
 * v is a vertice with in-degree of zero.
 * So, if we consider these possible starting
 * times in ascending order, you can DFS
 * down from each of these possible vertices.
 * 
 * Proof: If we consider these values in ascending
 * order, then all the values before this value are
 * already taken care of (because the +k adjustments
 * would have already been made), and the ones after
 * are taken care of (because minus intersecting paths,
 * their nodes don't need to be changed).
*/