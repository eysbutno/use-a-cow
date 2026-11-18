#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
    vector<int> e;
    DisjointSet(int n) : e(n, -1) {}
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool same_set(int x, int y) { return get(x) == get(y); }
    int size(int x) { return -e[get(x)]; }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int tt; cin >> tt;
    for (int i = 1; i <= tt; i++) {
        int n; cin >> n;
        vector a(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> a[i][j];
            }
        }
        vector b(n, vector<int>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> b[i][j];
            }
        }
        vector<int> r(n), c(n);
        for (int &i : r) { cin >> i; }
        for (int &i : c) { cin >> i; }
        vector<array<int, 3>> e;
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] != -1) { continue; }
                res += b[i][j];
                e.push_back({b[i][j], i, n + j});
            }
        }
        sort(begin(e), end(e), greater());
        DisjointSet dsu(2 * n);
        for (auto [w, u, v] : e) {
            if (dsu.unite(u, v)) {
                res -= w;
            }
        }
        cout << "Case #" << i << ": " << res << "\n";
    }
}
/**
 * Let's try to work in reverse. Say we start off with
 * some cell we don't know. Then, we can propogate to some
 * other cell in a row or column, which then propogates again.
 * Then, we get our subset of cells that "works". If we treat
 * each row and column as a node, and each cell as an edge,
 * then we actually want to find the Max Spanning Forest.
 * Each connected component has to be a tree because we can
 * only strictly determine the nodes that are leaves; everything
 * else cannot be determined because they rely on each other.
 */