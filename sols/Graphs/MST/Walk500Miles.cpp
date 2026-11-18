#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

ll dist(ll x, ll y) {
    return ((2019201913 * min(x, y) + 
        2019201949 * max(x, y)) % 2019201997);
}
vector<ll> prim(int n) {
    vector<bool> vis(n + 1);
    vector<ll> dists(n + 1, LONG_LONG_MAX);
    priority_queue<pair<int, int>> pq;
    pq.push({0, 1});
    dists[1] = 0;
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        if (vis[p.s]) continue;
        vis[p.s] = 1;
        for (int i = 1; i <= n; i++) {
            if (i != p.s && !vis[i] &&
                dist(p.s, i) < dists[i]) {
                dists[i] = dist(p.s, i);
                pq.push({-dists[i], i});
            }
        }
    }
    return dists;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
    int n, k; cin >> n >> k;
    vector<ll> dists = prim(n);
    sort(begin(dists), end(dists));
    cout << dists[n - k + 1];
}
/*
Use Prim's algorithm to construct
a MST. Removing the k heavest edges
gets you your final answer.
*/