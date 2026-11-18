#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define f first 
#define s second 
#define pb push_back
#define ins insert

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? 
            x : e[x] = get(e[x]); 
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
ll rem(ll x, ll y, ll m) {
    ll res = 1;
    x %= m;
    while (y > 0) {
        if (y % 2) {
            res = res * x % m;
        }
        x = x * x % m;
        y /= 2;
    }
    return res;
}
ll weight(ll x, ll y, ll m) {
    return ((rem(x, y, m) + rem(y, x, m)) % m);
}
int main() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    vector<pair<pii, ll>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            edges.pb({{i, j}, weight(a[i], a[j], m)});
        }
    }
    sort(begin(edges), end(edges),
        [&](auto& x, auto& y) {
        return x.s > y.s;
    });
    DSU dsu(n);
    ll weight = 0;
    for (auto& i : edges) {
        if (dsu.unite(i.f.f, i.f.s)) {
            weight += i.s;
        }
    }
    cout << weight << '\n';
}
/*
To efficiently calculate edge weights,
just use modular exponentiation.

Note that the optimal choices will
eventually lead to a MST.

Proof:
Observation 1: The optimal decisions
will lead to n - 1 events happening,
at least for each component.
Reasoning: Initially, you'll choose
the best edges. Later on, new edges
will be added between components because
it's just free points

Observation 2: The tree constructed must
be optimal, because you're finding max value.

Therefore, it's obvious that a MST is formed.
*/