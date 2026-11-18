#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

const int INF = 2e9;
struct Flight {
    int r, d, s;
    bool operator<(const Flight& y) const {
        return r > y.r;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<vector<Flight>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int c, r, d, s;
        cin >> c >> r >> d >> s;
        adj[c].push_back({r, d, s});
    }
    for (int i = 1; i <= n; i++) {
        sort(begin(adj[i]), end(adj[i]));
    }
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    priority_queue<pair<int, int>> pq;
    vector<int> time(n + 1, INF), idx(n + 1);
    time[1] = 0; pq.push({a[1], 1});
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        int l = p.s, t = -p.f;
        if (t != time[l] && l != 1) continue;
        while (idx[l] < size(adj[l]) &&
            adj[l][idx[l]].r >= t + a[l]) {
            Flight f = adj[l][idx[l]];
            if (f.s < time[f.d]) {
                time[f.d] = f.s;
                pq.push({-f.s, f.d});
            }
            idx[l]++;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (time[i] != INF) cout << time[i] << '\n';
        else cout << -1 << '\n';
    }
}
/*
Literally just Dijkstra's with
a few differences.
#1: We might visit a node
multiple times, because of
the negative edges.
#2: We can't process all
the edges at once, so we 
have a counter to select the 
next edge to process.
*/