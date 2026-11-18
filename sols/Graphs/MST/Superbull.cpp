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
    //freopen("superbull.in", "r", stdin);
    //freopen("superbull.out", "w", stdout);
    int n; cin >> n;
    vector<int> ids(n);
    for (int& i : ids) cin >> i;
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int val = ids[i] ^ ids[j];
            edges.push_back({{i, j}, val});
        }
    }
    sort(begin(edges), end(edges), [&](auto& x, auto& y) {
        return x.s > y.s;
    });
    DSU dsu(n); ll ans = 0;
    for (auto i : edges) {
        if (!dsu.connected(i.f.f, i.f.s)) {
            ans += i.s; dsu.unite(i.f.f, i.f.s);
        }
    }
    cout << ans << '\n';
}