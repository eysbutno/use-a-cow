#include <bits/stdc++.h>
using namespace std;
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
struct Edge {
    int s, d, w;
};
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("tractor.in", "r", stdin);
    freopen("tractor.out", "w", stdout);
    int n; cin >> n;
    int grid[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};
    vector<Edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 4; k++) {
                int r1 = i + dr[k], c1 = j + dc[k];
                if (r1 >= 0 && r1 < n && 
                    c1 >= 0 && c1 < n) {
                    edges.push_back({i * n + j, r1 * n + c1, 
                        abs(grid[i][j] - grid[r1][c1])});
                }
            }
        }
    }
    sort(begin(edges), end(edges), 
        [&](Edge& x, Edge& y) {
        return x.w < y.w;
    });
    DSU dsu(n * n);
    for (Edge& i : edges) {
        dsu.unite(i.s, i.d);
        if (dsu.size(i.s) >= 
            (n * n + 1) / 2) {
            cout << i.w << '\n';
            return 0;
        }
    }
}