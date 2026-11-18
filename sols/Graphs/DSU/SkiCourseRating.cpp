#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 
    
struct DSU {
    vector<int> e, s;
    DSU(int n) { 
        e = vector<int>(n, -1); 
        s = vector<int>(n);
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    void add(int x) {
        s[x]++;
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    ll unite(int x, int y, int d, int t) {
        x = get(x), y = get(y);
        if (x == y) return 0;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        s[x] += s[y];
        s[y] = 0;
        e[y] = x;
        if (-e[x] >= t) {
            ll temp = s[x];
            s[x] = 0;
            return temp * d;
        }
        return 0;
    }
};
const int MX = 501;
int grid[MX][MX], n, m, t;
int dr[]{1, 0, -1, 0},
    dc[]{0, 1, 0, -1};
int id(int r, int c) {
    return r * m + c;
}
bool valid(int r, int c) {
    return (r >= 0 && r < n &&
            c >= 0 && c < m);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }
    vector<pair<int, pii>> edges;
    auto addEdge = [&](int i, int j) {
        for (int k = 0; k < 2; k++) {
            int r = i + dr[k], 
                c = j + dc[k];
            if (valid(r, c)) {
                int D = abs(grid[r][c] - grid[i][j]);
                edges.pb({D, {id(r, c), id(i, j)}});
            }
        }
    };
    DSU dsu(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            bool c; cin >> c;
            if (c) dsu.add(id(i, j));
            addEdge(i, j);
        }
    }
    ll sum = 0;
    sort(all(edges));
    for (auto& i : edges) {
        int x = i.s.f, y = i.s.s, 
            w = i.f;
        sum += dsu.unite(x, y, w, t);
    }
    cout << sum << '\n';
}
/**
 * Idea: Have an array within
 * the DSU to store how many
 * "Starting Points" are in each
 * component. If uniting two components
 * makes the size >= t, then add t * d
 * to the result. (Sort connections
 * in ascending order of d)
*/