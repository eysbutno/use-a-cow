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
        return e[x] < 0 ? x : e[x] = get(e[x]); 
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
const int MAX = 2e5 + 1;
int cost[MAX], n;
vector<int> perm[MAX];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    DSU dsu(n * 2 + 1);
    vector<int> ord(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cost[i];
        vector<int> temp(4);
        for (int& j : temp) {
            cin >> j;
        }
        for (int j = 0; j < 4; j += 2) {
            dsu.unite(temp[j], temp[j + 1]);
        }
        ord[i] = i;
        perm[i] = temp;
    }
    sort(begin(ord) + 1, end(ord),
        [&](int x, int y) {
        return cost[x] < cost[y];
    });
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int idx = ord[i];
        if (dsu.unite(perm[idx][0], perm[idx][2])) {
            res += cost[idx];
        }
    }
    cout << res << '\n';
}
/*
Observation 1:
Each unique "position" is
essentially just a portal,
not a portal location pair.
Reasoning: A portal can change
locations. Obviously.

Observation 2:
If the graph is just portals
with adjacent portals being edges,
the graph is a bunch of disjoint cycles.
Reasoning: degree of 2 for each node -> cycles.

Observation 3:
To unite cycles, you just need to permutate
the portals in one of them. 
Reasoning: By swapping elements,
you add two edges between the cycles.

Observation 4:
You end up using Kruskals to unify everything.
*/