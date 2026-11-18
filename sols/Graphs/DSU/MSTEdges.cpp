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
const int INF = 1e9 + 7;
struct DisjointSet {
    vector<int> e, t;
    DisjointSet(int n) { 
        e = vector<int>(n, -1); 
        t = vector<int>(n, INF);
    }
    int get(int x) { return e[x] < 0 ? x : get(e[x]); }
    bool unite(int x, int y, int w) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x, t[y] = w;
        return true;
    }
    int ask(int x, int y) {
        int res = 0;
        while (x != y) {
            if (t[x] > t[y]) swap(x, y);
            res = t[x], x = e[x];
        }
        return res;
    }
};
void solve() {
    int n, m; cin >> n >> m;
    vector<array<int, 4>> e(m);
    for (int i = 0; i < m; i++) {
        cin >> e[i][0] >> e[i][1] >> e[i][2];
        --e[i][0], --e[i][1], e[i][3] = i;
    }
    sort(all(e), [&](auto i, auto j) {
        return i[2] < j[2];
    });
    DisjointSet dsu(n);
    vector<ll> res(m, -1);
    ll sum = 0; // result
    for (int i = 0; i < m; i++) {
        auto [u, v, w, id] = e[i];
        if (dsu.unite(u, v, w)) {
            res[id] = 0, sum += w;
        }
    }
    for (int i = 0; i < m; i++) {
        auto [u, v, w, id] = e[i];
        if (!res[id]) {
            res[id] = sum;
        } else {
            res[id] = sum - dsu.ask(u, v) + w;
        }
    }
    for (int i = 0; i < m; i++) {
        cout << res[i] << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * First, build the MST and build a
 * Kruskal tree. Every edge in the MST can
 * be ignored. Then, we query the max edge
 * on the path from u to v.
 * 
 * NOTE: While binlift-RMQ is an option, that's
 * really gross, ngl. DSU RMQ is so much nicer.
*/