#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first
#define s second

const int N = 1e4 + 1;
const ll LINF = 1e18;
const int INF = 1e9;
vector<pii> adj[N];
struct Node {
    ll f, s, p;
    bool operator<(Node y) const {
        return f > y.f;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("shortcut.in", "r", stdin);
    freopen("shortcut.out", "w", stdout);
    int n, m, t;
    cin >> n >> m >> t;
    vector<ll> c(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b, d;
        cin >> a >> b >> d;
        adj[a].pb({b, d});
        adj[b].pb({a, d});
    }
    vector<ll> dist(n + 1, LINF);
    vector<int> prev(n + 1, INF);
    priority_queue<Node> q;
    dist[1] = 0;
    prev[1] = 0;
    q.push({0, 1, 0});
    while (!q.empty()) {
        auto N = q.top(); q.pop();
        int u = N.s, t = N.f, p = N.p;
        if (prev[u] != p) continue;
        for (auto i : adj[u]) {
            int v = i.f, w = i.s;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                q.push({dist[v], v, u});
                prev[v] = u;
            } else if (dist[u] + w == dist[v]
                && u < prev[v]) {
                q.push({dist[v], v, u});
                prev[v] = u;
            }
        }
    }
    vector<ll> occ(n + 1);
    for (int i = 1; i <= n; i++) {
        int cur = i;
        while (cur != INF) {
            occ[cur] += c[i];
            cur = prev[cur];
        }
    }
    ll res = 0;
    for (int i = 2; i <= n; i++) {
        ll pos = occ[i] * (dist[i] - t);
        res = max(res, pos);
    }
    cout << res << '\n';
}