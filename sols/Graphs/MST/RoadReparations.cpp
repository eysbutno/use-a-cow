#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second

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
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<pair<pair<int, int>, int>> edges(m);
    for (auto& i : edges) cin >> i.f.f >> i.f.s >> i.s;
    sort(begin(edges), end(edges), [&](auto& x, auto& y) {
        return x.s < y.s;
    });
    DSU dsu(n + 1);
    ll cost = 0;
    vector<bool> con(n + 1);
    for (auto& i : edges) {
        if (!dsu.connected(i.f.f, i.f.s)) {
            cost += i.s; dsu.unite(i.f.f, i.f.s);
            con[i.f.f] = 1, con[i.f.s] = 1;
        }
    }
    if (dsu.size(1) != n) cout << "IMPOSSIBLE" << '\n';
    else cout << cost << '\n';
}