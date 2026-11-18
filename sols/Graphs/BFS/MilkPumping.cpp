#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 
 
struct Edge {
    int t, c, f;
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    freopen("pump.in", "r", stdin);
    freopen("pump.out", "w", stdout);
    int n, m; cin >> n >> m;
    vector<vector<Edge>> adj(n + 1);
    set<int> flowRate;
    for (int i = 0; i < m; i++) {
        int a, b, c, f; 
        cin >> a >> b >> c >> f;
        adj[a].push_back({b, c, f});
        adj[b].push_back({a, c, f});
        flowRate.insert(f);
    }
    auto cost = [&](int flow) {
        vector<int> dist(n + 1, 2e9);
        vector<bool> vis(n + 1);
        priority_queue<pii> q;
        dist[1] = 0; q.push({0, 1});
        while (!q.empty()) {
            int p = q.top().s; q.pop();
            if (vis[p]) continue;
            vis[p] = 1;
            for (auto& i : adj[p]) {
                int v = i.t, w = i.c,
                    f = i.f;
                if (dist[p] + w < dist[v]
                    && f >= flow) {
                    dist[v] = dist[p] + w;
                    q.push({-dist[v], v});
                }
            }
        }
        return dist[n];
    };
    double best = -1;
    for (int i : flowRate) {
        double res = cost(i);
        double ratio = i / res;
        if (ratio > best) best = ratio;
    }
    best *= 1e6;
    cout << (int) best << '\n';
}
/*
Milk pumping....
Brute force flow rate,
and find out minimal cost.
Kabam.

NOTE: There exists a faster
solution. All you need to do
is find max path by maintaining
the current min flow and cost lol.
*/