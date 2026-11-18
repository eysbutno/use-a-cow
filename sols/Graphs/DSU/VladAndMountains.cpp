#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
struct DisjointSet {
    vector<int> e;
    DisjointSet(int n) { e = vector<int>(n, -1); }
    int size(int x) { return -e[get(x)]; }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    int same_set(int x, int y) { return get(x) == get(y); }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};
void solve() {
    int n, m; 
    cin >> n >> m;
    vector<int> h(n);
    vector<array<int, 2>> cpy(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i], cpy[i] = {h[i], i};
    }
    sort(all(cpy));
    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    int q; cin >> q;
    vector<array<int, 4>> t(q);
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> t[i][j];
        }
        --t[i][0], --t[i][1], t[i][3] = i;
    }
    sort(all(t), [&](auto i, auto j) {
        return h[i[0]] + i[2] < h[j[0]] + j[2];
    });
    vector<bool> active(n);
    DisjointSet dsu(n);
    int ptr = 0;
    auto join = [&](int u) -> void {
        for (int v : adj[u]) {
            if (active[v]) dsu.unite(u, v);
        }
        active[u] = true;
    };
    vector<bool> res(q);
    for (auto [a, b, e, id] : t) {
        while (ptr < n && cpy[ptr][0] <= h[a] + e) {
            join(cpy[ptr][1]), ++ptr;
        }
        res[id] = dsu.same_set(a, b);
    }
    for (bool i : res) {
        cout << (i ? "YES" : "NO") << "\n";
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Vlad and the Mountains (CF)
 * i -> j -> k: h_j - h_i + h_k - h_j = h_k - h_i.
 * Therefore, the problem basically asks: 
 * Is there a path from A to B, such that h_i - h_a <= e?
 * 
 * We can sort the mountains by height, initially. Note
 * that the height cannot exceed h_a + e, so we include
 * all the mountains with heights <= that.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/