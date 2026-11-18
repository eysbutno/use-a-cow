#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
#define ll long long
// Moocast Gold
struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
struct Edge {
    int x, y; ll w;
};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
    int n; cin >> n;
    vector<pair<int, int>> locs(n);
    for (auto& i : locs) cin >> i.f >> i.s;
    vector<Edge> edges; 
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int dx = locs[i].f - locs[j].f;
            int dy = locs[i].s - locs[j].s;
            edges.push_back({i, j, (ll) 
                dx * dx + dy * dy});
        }
    }
    sort(begin(edges), end(edges), [&](Edge& x, Edge& y) {
        return x.w < y.w;
    });
    ll ans = 0;
    DSU dsu(n);
    for (Edge& i : edges) {
        if (!dsu.connected(i.x, i.y)) {
            dsu.unite(i.x, i.y); ans = i.w;
        }
    }
    cout << ans << '\n';
}
/*
Create a list of all the possible edges and sort
that list by weight. Use a DSU to maintain the current connected
components. If two edges are in different components,
unite them. The last edge weight you unite is the final answer.
*/