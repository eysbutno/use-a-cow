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
void solve() {
    int n, m; 
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    const int l = n / 2, r = (n + 1) / 2;
    vector<int> mis(1 << l);
    for (int i = 0; i < (1 << l); i++) {
        bool works = true;
        for (int j = 0; j < l; j++) {
            if (!(i >> j & 1)) continue;
            for (int k : adj[j]) {
                if (k < l && (i >> k & 1)) {
                    works = false;
                    break;
                }
            }
            if (!works) break;
        }
        if (works) mis[i] = i;
    }
    auto btc = [&](int x) -> int {
        return __builtin_popcount(x);
    };
    for (int i = 0; i < (1 << l); i++) {
        for (int j = 0; j < l; j++) {
            if (!(i >> j & 1)) continue;
            if (btc(mis[i]) < btc(mis[i ^ (1 << j)])) {
                mis[i] = mis[i ^ (1 << j)];
            }
        }
    }
    int resl = 0, resr = 0;
    for (int i = 0; i < (1 << r); i++) {
        bool works = true;
        for (int j = 0; j < r; j++) {
            if (!(i >> j & 1)) continue;
            for (int k : adj[l + j]) if (k >= l) {
                if (i >> (k - l) & 1) {
                    works = false;
                    break;
                }
            }
            if (!works) break;
        }
        if (!works) continue;
        int good = (1 << l) - 1;
        for (int j = 0; j < r; j++) {
            if (!(i >> j & 1)) continue;
            for (int k : adj[l + j]) if (k < l) {
                if (good >> k & 1) good ^= 1 << k;
            }
        }   
        if (btc(i) + btc(mis[good]) > btc(resl) + btc(resr)) {
            resl = mis[good], resr = i;
        }
    }
    cout << btc(resl) + btc(resr) << "\n";
    for (int i = 0; i < l; i++) {
        if (resl >> i & 1) {
            cout << i << " ";
        }
    }
    for (int i = 0; i < r; i++) {
        if (resr >> i & 1) {
            cout << l + i << " ";
        }
    }
    cout << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * For each mask, calculate the best submask
 * that is an independent set. (For the left part)
 * 
 * Then, for the right mask, check if this mask works.
 * Afterwards, we keep a list of nodes that CANNOT be inside
 * our left mask. Then, because of our previous precalculation, it
 * becomes trivial.
*/