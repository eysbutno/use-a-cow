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

int travel_plan(int N, int M, int R[][2], 
    int L[], int k, int p[]) {
    const ll INF = 1e18;
    int n = N, m = M;
    vector<vector<pii>> adj(n);
    for (int i = 0; i < m; i++) {
        int x = R[i][0], y = R[i][1],
            w = L[i];
        adj[x].pb({y, w});
        adj[y].pb({x, w});
    }
    vector<vector<ll>> dist(2, 
        vector<ll>(n, INF));
    priority_queue<pll> pq;
    for (int i = 0; i < k; i++) {
        pq.push({0, p[i]});
        dist[0][p[i]] = 0;
        dist[1][p[i]] = 0;
    }
    while (!pq.empty()) {
        auto N = pq.top(); pq.pop();
        ll u = N.s, t = -N.f;
        if (dist[1][u] != t) {
            continue;
        }
        for (auto [v, w] : adj[u]) {
            if (t + w < dist[0][v]) {
                if (dist[0][v] != dist[1][v]) {
                    pq.push({-dist[0][v], v});
                }
                swap(dist[0][v], dist[1][v]);
                dist[0][v] = t + w;
            } else if (t + w < dist[1][v]) {
                dist[1][v] = t + w;
                pq.push({-dist[1][v], v});
            }
        }
    }
    return (int) dist[1][0];
}
/**
 * Problem: IOI 2011 - Crocodile.
 * Observations:
 * 1. You will never go backwards.
 * 2. Worst case, you always take the
 * second best route forward, because
 * the crocodile will block the best
 * route possible.
 * 
 * Run Dijkstra from each escape, 
 * basing each distance off the second
 * best possibility for each node.
*/