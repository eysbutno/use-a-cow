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
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, d; cin >> n >> d;
    DSU dsu(n + 1);
    int useless = 1;
    while (d--) {
        int x, y; cin >> x >> y;
        if (!dsu.unite(x, y)) ++useless;
        vector<int> sz;
        for (int i = 1; i <= n; i++) {
            if (dsu.get(i) == i) {
                sz.push_back(dsu.size(i));
            }
        }
        sort(begin(sz), end(sz), greater<int>());
        int it = min((int) size(sz), useless), res = 0;
        for (int i = 0; i < it; i++) {
            res += sz[i];
        }
        cout << res - 1 << '\n';
    }
}
/*
When adding edges, there are two cases:
C1: Two people in different components.
- Just unite the components.
C2: In the same component.
- Treat it like an extra edge we're given.
To get our answer, it's the sum of all
the connected components we can unite
with our extra edges minus one.
- Why? Because we can always restructure a
connected component with N nodes and N-1 
edges to be a tree with one node connecting
to all the other nodes, thus giving the best
answer possible.
*/