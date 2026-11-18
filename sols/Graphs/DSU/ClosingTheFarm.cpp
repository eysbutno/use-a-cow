#include <bits/stdc++.h>
using namespace std;

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
    freopen("closing.in", "r", stdin);
    freopen("closing.out", "w", stdout);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int> ord(n), ans(n);
    for (int& i : ord) cin >> i;
    DSU dsu(n + 1);
    set<int> open;
    for (int i = n - 1; i >= 0; i--) {
        for (int j : adj[ord[i]]) {
            if (open.count(j)) {
                dsu.unite(ord[i], j);
            }
        }
        ans[i] = dsu.size(ord[i]) == n - i;
        open.insert(ord[i]);
    }
    for (int i = 0; i < n; i++) {
        if (ans[i]) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
}
/*
Reverse the process: add barns and check
connectivity.
*/