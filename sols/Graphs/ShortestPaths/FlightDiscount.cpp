#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

const int MAX = 1e5 + 1;
vector<pii> adj[2][MAX];
vector<ll> calcDist(
    int n, int id, int st) {
    vector<ll> dists(n + 1, 1e18);
    dists[st] = 0;
    vector<bool> vis(n + 1);
    priority_queue<pair<ll, int>> q;
    dists[st] = 0; q.push({0, st});
    while (!q.empty()) {
        int p = q.top().s; q.pop();
        if (vis[p]) continue;
        vis[p] = 1;
        for (auto i : adj[id][p]) {
            int v = i.f, w = i.s;
            if (dists[p] + w < dists[v]) {
                dists[v] = dists[p] + w;
                q.push({-dists[v], v});
            }
        }
    }
    return dists;
}
int main() {
    int n, m; cin >> n >> m;
    vector<pair<pii, ll>> edges;
    for (int i = 0; i < m; i++) {
        int a, b, c; 
        cin >> a >> b >> c;
        adj[0][a].push_back({b, c});
        adj[1][b].push_back({a, c});
        edges.push_back({{a, b}, c});
    }
    vector<ll> dist1 = calcDist(n, 0, 1),
        dist2 = calcDist(n, 1, n);
    ll res = 1e18;
    for (auto& i : edges) {
        res = min(res, i.s / 2 + 
            dist1[i.f.f] + dist2[i.f.s]);
    }
    cout << res << '\n';
}