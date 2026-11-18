#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int K = 51;
const int INF = 1e9;
vector<int> adj[K];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, k; cin >> n >> k;
    vector<unordered_set<int>> locs(k + 1);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        locs[b[i]].ins(i);
    }
    for (int i = 1; i <= k; i++) {
        for (int j = 1; j <= k; j++) {
            char ok; cin >> ok;
            if (ok == '1') adj[i].pb(j);
        }
    }
    vector<int> dist(n, INF);
    dist[0] = 0;
    priority_queue<pii> pq;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [t, u] = pq.top(); 
        pq.pop(), t *= -1;
        if (dist[u] != t) {
            continue;
        }
        locs[b[u]].erase(u);
        for (int i : adj[b[u]]) {
            for (int j : locs[i]) {
                int dx = abs(u - j);
                if (t + dx < dist[j]) {
                    dist[j] = t + dx;
                    pq.push({-dist[j], j});
                }
            }
        }
    }
    cout << (dist.back() != INF 
        ? dist.back() : -1);
}
/**
 * TASK: Telephone.
 * Algorithm: Just Dijkstra
 * it. 
 * 
 * NOTE: IDK if this solution
 * is intended, cuz I had to
 * optimize a bunch.
*/