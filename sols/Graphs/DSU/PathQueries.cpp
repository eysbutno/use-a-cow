#include <bits/stdc++.h>
using namespace std;
#define ll long long
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
ll sum(int val) {
    return ((ll) val * (val - 1)) / 2;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m; cin >> n >> m;
    vector<pair<pair<int, int>, int>> edges(n - 1);
    for (int i = 1; i < n; i++) {
        int u, v, w; cin >> u >> v >> w;
        edges[i - 1] = {{u, v}, w};
    }
    sort(begin(edges), end(edges),
        [&](auto& x, auto& y) {
        return x.s < y.s;
    });
    vector<pair<int, int>> query(m);
    for (int i = 0; i < m; i++) {
        cin >> query[i].f;
        query[i].s = i;
    }
    sort(begin(query), end(query));
    int ptr = 0;
    ll res = 0;
    DSU dsu(n + 1);
    vector<ll> ans(m);
    for (int i = 0; i < m; i++) {
        int mx = query[i].f;
        while (ptr < n - 1 && 
            edges[ptr].s <= mx) {
            int u = edges[ptr].f.f,
                v = edges[ptr].f.s;
            res -= sum(dsu.size(u));
            res -= sum(dsu.size(v));
            dsu.unite(u, v);
            res += sum(dsu.size(u));
            ++ptr;
        }
        ans[query[i].s] = res;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}
/*
Fun problem, it's basically
Mootube with a combinatorics
twist.
*/