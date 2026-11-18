#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

struct DSU {
    vector<int> e;
    DSU(int n) { e = vector<int>(n, -1); }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y], e[y] = x;
        return true;
    }
};
const int MOD = 998244353;
ll expo(ll x, ll n) {
    x %= MOD;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}
void solve() {
    int n, s; cin >> n >> s;
    vector<array<int, 3>> e;
    for (int i = 1; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        e.push_back({--x, --y, w});
    }
    sort(all(e), [&](auto& x, auto& y) {
        return x[2] < y[2];
    });
    DSU dsu(n);
    ll res = 1;
    for (auto [x, y, w] : e) {
        x = dsu.get(x), y = dsu.get(y);
        ll sz = (ll) dsu.e[x] * dsu.e[y] - 1;
        res *= expo(s - w + 1, sz), res %= MOD;
        dsu.unite(x, y);
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Counting Graphs (CF).
 * Think of the problem from the perspective
 * of adding new edges in. Every edge WILL 
 * unite two components. So, when adding edges
 * between these two components, we must ensure that
 * the chosen edge will still get chosen by a MST
 * algorithm. So, you can create a bunch of edges
 * between all nodes in each component. Kind of.
*/