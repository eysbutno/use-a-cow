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
    vector<int> c(n);
    for (int& i : c) {
        cin >> i, --i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[--x].push_back(--y);
        adj[y].push_back(x);
    }
    ll tot = 0;
    vector<map<int, int>> occ(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        int big = -1;
        for (int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
            if (big == -1 || sz(occ[v]) > sz(occ[big])) {
                big = v;
            }
        }
        for (int v : adj[u]) if (v != p && v != big) {
            for (auto [k, v] : occ[v]) {
                if (k != c[u]) tot += (ll) v * occ[big][k];
                occ[big][k] += v;
            }
        }
        if (big != -1) swap(occ[u], occ[big]);
        tot += occ[u][c[u]], occ[u][c[u]] = 1;
    }; dfs(0, -1, dfs);
    cout << tot << '\n';
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: E. Count Paths (CF).
 * Idea: Root the tree arbitrarily. Maintain all the
 * top nodes. For all children nodes top colors, that
 * are different than this one's top color, you can
 * unite them. Otherwise, just pair with this current
 * node.
 * 
 * Note that Small-To-Large merging is needed so
 * it doesn't TLE.
*/
/**
  * Make observations.
  * Try out various techniques in your head.
  * See if there are some "restrictions" that you
  * can place, to limit it to a set of states. This
  * often makes life a million times easier!
  * Actually do something and don't just stare at
  * the screen....!
*/
/*
const int MOD = 1e9 + 7;
template<class T> void add(T& a, T b) {
	a += b, a %= MOD;
}
template<class T> void sub(T& a, T b) {
	a > b ? a -= b : a -= b, a += MOD;
}
template<class T> void mul(T& a, T b) {
	a = (a * b) % MOD;
}
*/