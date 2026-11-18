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
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    const int LOG = 17;
    const int MX = 10;
    using Info = vector<int>;
    vector up(LOG, vector(n, 0));
    vector data(LOG, vector(n, Info()));
    for (int i = 1; i <= m; i++) {
        int c; cin >> c;
        data[0][--c].push_back(i);
    }
    auto merge = [&](Info &a, Info &b, int mx) -> Info {
        vector<int> res;
        int i = 0, j = 0;
        while (sz(res) < mx && i < sz(a) && j < sz(b)) {
            if (a[i] < b[j]) {
                res.push_back(a[i]), ++i;
            } else {
                res.push_back(b[j]), ++j;
            }
        }
        while (sz(res) < mx && i < sz(a)) {
            res.push_back(a[i]), ++i;
        }
        while (sz(res) < mx && j < sz(b)) {
            res.push_back(b[j]), ++j;
        }
        return res;
    };
    vector<int> dep(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        for (int i = 1; i < LOG; i++) {
            int split = up[i - 1][u];
            up[i][u] = up[i - 1][split];
            data[i][u] = merge(data[i - 1][u], data[i - 1][split], 10);
        }
        for (int v : adj[u]) if (v != p) {
            up[0][v] = u, dep[v] = dep[u] + 1;
            dfs(v, u, dfs);
        }
    }; dfs(0, -1, dfs);
    auto query = [&]() -> Info {
        int u, v, a;
        cin >> u >> v >> a;
        --u, --v;
        if (dep[u] < dep[v]) swap(u, v);
        int dx = dep[u] - dep[v];
        Info fst, snd;
        for (int i = LOG - 1; i >= 0; i--) {
            if (dx >> i & 1) {
                fst = merge(fst, data[i][u], a);
                u = up[i][u];
            }
        }
        if (u == v) {
            return merge(fst, data[0][u], a);
        } else {
            for (int i = LOG - 1; i >= 0; i--) {
                if (up[i][u] != up[i][v]) {
                    fst = merge(fst, data[i][u], a);
                    snd = merge(snd, data[i][v], a);
                    u = up[i][u], v = up[i][v];
                }
            }
            fst = merge(fst, data[1][u], a);
            snd = merge(snd, data[0][v], a);
            return merge(fst, snd, a);
        }
    };
    while (q--) {
        auto res = query();
        int z = sz(res);
        cout << z << " ";
        for (int i = 0; i < z; i++) {
            cout << res[i] << " ";
        }
        cout << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * E. Duff in the Army (CF)
 * - Given N cities in a tree, and M people
 *   who live in a given city. 
 * - Each query: for a query {u, v, a}, 
 *   print out the first a ids on the path.
 * 
 * **NOTE** a is strictly bounded to be at 10.
 * So, we can just binlift, and bash.
*/