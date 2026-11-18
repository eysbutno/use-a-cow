#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

#ifdef LOCAL
#include "../src/debug.hpp"
#else
#define debug(...) 420
#endif
// g++ -DLOCAL -Wall Practice.cpp -o bin

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
struct DisjointSet {
    vector<int> e;
    DisjointSet(int n) : e(n, -1) {}
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
void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (int &i : p) {
        cin >> i;
    }
    sort(all(p));
    p.erase(unique(all(p)), end(p));
    const int MX = p.back();
    n = sz(p);
    vector<int> nxt(MX + 1, -1);
    for (int i = 0; i < n; i++) {
        nxt[p[i]] = i;
    }
    for (int i = MX - 1; i >= 1; i--) {
        if (nxt[i] == -1) nxt[i] = nxt[i + 1];
    }
    vector<vector<pii>> edges(MX + 1);
    for (int i = 0; i + 1 < n; i++) {
        edges[p[i + 1] % p[i]].push_back({i, i + 1});
        for (int j = p[i] * 2; j <= MX; j += p[i]) {
            edges[p[nxt[j]] % p[i]].push_back({i, nxt[j]});
        }
    }
    ll res = 0;
    DisjointSet dsu(n);
    for (int i = 0; i <= MX; i++) {
        for (auto [u, v] : edges[i]) {
            if (dsu.unite(u, v)) res += i;
        }
    }
    cout << res << "\n";  
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Instead of linking up indices, we are
 * interested in linking up numbers, per se.
 * Assume we have some number N. All other numbers
 * that are greater than N can be represented as 
 * KN + v. Obviously, we want to minimize v. So, we
 * can brute force every value of K (because harmonic).
*/