#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;
ll dist[MAX], ways[MAX];
int most[MAX], least[MAX];
int main() {
    int n, m; cin >> n >> m;
    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({y, w});
    }
    for (int i = 2; i <= n; i++) {
        dist[i] = LINF;
    }
    ways[1] = 1;
    priority_queue<pll> pq;
    pq.push({0, 1});
    while (!pq.empty()) {
        auto N = pq.top(); pq.pop();
        ll t = -N.f, u = N.s;
        if (dist[u] != t) continue;
        for (auto& i : adj[u]) {
            int v = i.f, w = i.s;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                ways[v] = ways[u] % MOD;
                most[v] = most[u] + 1;
                least[v] = least[u] + 1;
                pq.push({-dist[v], v});
            }
            else if (dist[u] + w == dist[v]) {
                ways[v] += ways[u];
                ways[v] %= MOD;
                ckmax(most[v], most[u] + 1);
                ckmin(least[v], least[u] + 1);
            }
        }
    }
    cout << dist[n] << ' ' << ways[n] << ' '
        << least[n] << ' ' << most[n];
}
/**
 * Dijkstras + some DP ideas.
 * Note:
 * The reason we can just add the # of ways
 * immediately and not have to worry about a node
 * not processing is because of the edge weights
 * being positive; thus, once you get to a node,
 * you can safely assume dist[i], ways[i],
 * most[i], and least[i] are correctly
 * computed.
*/