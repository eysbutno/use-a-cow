#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
#define ll long long

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
    freopen("mootube.in", "r", stdin);
    freopen("mootube.out", "w", stdout);
    int n, q; cin >> n >> q;
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 1; i < n; i++) {
        int p, q, r; cin >> p >> q >> r;
        edges.push_back({{--p, --q}, r});
    }
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        int k, v; cin >> k >> v;
        queries[i] = {k, --v};
    }
    vector<int> ids(q);
    for (int i = 0; i < q; i++) {
        ids[i] = i;
    }
    sort(begin(ids), end(ids), [&](int x, int y) {
        return queries[x].f > queries[y].f;
    });
    sort(begin(edges), end(edges), [&](auto& x, auto& y) {
        return x.s > y.s;
    });
    vector<int> ans(q);
    DSU dsu(n);
    int cnt = 0;
    for (int i = 0; i < q; i++) {
        auto query = queries[ids[i]];
        while (cnt < n - 1 && edges[cnt].s >= query.f) {
            dsu.unite(edges[cnt].f.f, edges[cnt].f.s); ++cnt;
        }
        ans[ids[i]] = dsu.size(query.s);
    }
    for (int i : ans) cout << i - 1 << '\n';
}
/*
Sort the edges and the queries by relevance.
Unite videos that have high enough relevance for the query.
*/