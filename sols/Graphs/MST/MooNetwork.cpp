#include <bits/stdc++.h>
using namespace std; 
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
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
ll dist(pll a, pll b) {
    ll dx = a.f - b.f;
    ll dy = a.s - b.s;
    return dx * dx + dy * dy;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vector<pll> l(n);
    for (auto& i : l) {
        cin >> i.f >> i.s;
    }
    sort(begin(l), end(l));
    vector<int> idx(11, -1);
    vector<pair<pii, ll>> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= 10; j++) {
            if (idx[j] != -1) {
                edges.pb({{i, idx[j]}, 
                    dist(l[i], l[idx[j]])});
            }
        }
        idx[l[i].s] = i;
    }
    sort(begin(edges), end(edges),
        [&](auto& x, auto& y) {
        return x.s < y.s;
    });
    ll cost = 0;
    DSU dsu(n);
    for (auto& i : edges) {
        if (dsu.unite(i.f.f, i.f.s)) {
            cost += i.s;
        }
    }
    cout << cost << '\n';
}
/*
Observation 1:
The graph will become a MST.

Observation 2:
y is in the set [0, 10].

Observation 3:
For a given y value, it's
always optimal to build an edge
to only the closest x valued edge.

Reasoning:
Say we have three edges 1, 2, and 3,
and edges 1 and 2 have the same y value.
It's never optimal to link edges 1 and 3, 
because for every combination of unique
components, it's always better to unite
1 & 2, 2 & 3, or both.

(If I was actually good at math I would 
have made the easy observation lol)

Note: Learn to like, use line sweep for 
grid problems because line sweep is actually
ridiculously overpowered.
*/