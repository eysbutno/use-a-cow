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
struct DSU {
    vector<int> e;
    DSU(int n) { e = vector<int>(n, -1); }
    int size(int x) { return -e[get(x)]; }
    int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};
void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 2>> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i][0] >> edges[i][1];
        if (edges[i][0] > edges[i][1]) {
            swap(edges[i][0], edges[i][1]);
        }
    }
    sort(all(edges), greater<>());
    DSU dsu(n + 1);
    for (auto [u, v] : edges) {
        if (dsu.unite(u, v)) {
            cout << u << " " << v << "\n";
        }
    }
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: F. Minimize Degrees (BAPC)
 * It's obviously optimal to unite as much
 * stuff as possible w/ the lexicographically
 * maximum edges first. So, do that, then move
 * towards the top.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/