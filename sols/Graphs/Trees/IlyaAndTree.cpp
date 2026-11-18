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
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<int> res(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        // precalculating the answer, if res[0] = 0.
        for (int v : adj[u]) if (v != p) {
            res[v] = gcd(res[u], a[v]);
            dfs(v, u, dfs);
        }
    }; dfs(0, -1, dfs);
    res[0] = a[0];
    auto apply = [&](int x) -> void {
        // Try "applying" divisor x as the answer.
        auto dfs2 = [&](int u, int p, int bad,
                        auto&& dfs2) -> void {
            bad += (a[u] % x != 0);
            if (bad > 1) return;
            smax(res[u], x);
            for (int v : adj[u]) if (v != p) {
                dfs2(v, u, bad, dfs2);
            }
        }; dfs2(0, -1, 0, dfs2);
    };
    for (int i = 1; i * i <= a[0]; i++) {
        if (a[0] % i == 0) {
            apply(a[0] / i), apply(i);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Either the root is set to 0, or
 * it isn't. If the root is not set to zero,
 * any answer MUST be some divisor of the root.
*/