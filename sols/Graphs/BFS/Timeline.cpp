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
vector<pii> adj[N];
int inDeg[N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("timeline.in", "r", stdin);
    freopen("timeline.out", "w", stdout);
    int n, m, c; cin >> n >> m >> c;
    vector<int> s(n);
    for (int& i : s) {
        cin >> i;
    }
    for (int i = 0; i < c; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[--x].pb({--y, w});
        inDeg[y]++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) q.push(i);
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto [v, w] : adj[u]) {
            --inDeg[v];
            ckmax(s[v], s[u] + w);
            if (!inDeg[v]) {
                q.push(v);
            }
        }
    }
    for (int i : s) {
        cout << i << '\n';
    }
}
/**
 * Do TopoSort (using BFS) to 
 * adjust each node to be the maximum
 * day necessary.
 * 
 * NOTE: The dates of the sessions are 
 * not necessarily unique. Silly me.
*/