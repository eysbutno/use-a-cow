#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
namespace SegmentTree {
    template <typename F>
    void forRange(int lf, int rt, F f) {
        for (; lf < rt; lf >>= 1, rt >>= 1) {
            if (lf & 1) f(lf++);
            if (rt & 1) f(--rt);
        }
    } 
    int log2(int x) {
        return 31 - __builtin_clz(x);
    }
    int size(int x) {
        return 1 << log2(2 * x - 1);
    }
    template <typename F>
    void forParents(int p, bool dir, F f) {
        const int lvls = log2(p);
        for (int i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
    template<class T, class U>
    void update(int l, int r, T apply, U pull) {
        forRange(l, r, apply);
        forParents(l, true, pull);
        forParents(r - 1, true, pull);
    }
    template<class T, class U>
    void query(int l, int r, T push, U apply) {
        forParents(l, false, push);
        forParents(r - 1, false, push);
        forRange(l, r, apply);
    }
}
void solve() {
    int q, cnt = 1; cin >> q;
    vector<vector<int>> adj(q + 1);
    vector<array<int, 3>> upd(q);
    for (int i = 0; i < q; i++) {
        int t; cin >> t;
        if (t == 1) {
            int v; cin >> v;
            adj[--v].push_back(cnt++);
            upd[i] = {t, v, cnt - 1};
        } else {
            int v, x; cin >> v >> x;
            upd[i] = {t, --v, x};
        }
    }
    vector<int> tin(cnt), tout(cnt);
    int timer = 0;
    auto tour = [&](int u, auto&& tour) -> void {
        tin[u] = timer++;
        for (int v : adj[u]) {
            tour(v, tour);
        }
        tout[u] = timer;
    }; tour(0, tour);
    const int SZ = timer;
    vector<ll> t(SZ << 1), lz(SZ);
    vector<int> len(SZ << 1);
    for (int i = 0; i < timer; i++) {
        len[SZ + i] = 1;
    }
    for (int i = SZ - 1; i >= 1; i--) {
        len[i] = len[i << 1] + len[i << 1 | 1];
    }
    const auto pull = [&](int idx) -> void {
        t[idx] = t[idx << 1] + t[idx << 1 | 1];
        t[idx] += lz[idx] * len[idx];
    };
    const auto apply = [&](int idx, ll amt) -> void {
        t[idx] += 1LL * len[idx] * amt;
        if (idx < SZ) lz[idx] += amt;
    };
    const auto push = [&](int idx) -> void {
        apply(idx << 1, lz[idx]);
        apply(idx << 1 | 1, lz[idx]);
        lz[idx] = 0;
    };
    for (auto [type, a, b] : upd) {
        if (type == 1) {
            ll cur = 0;
            SegmentTree::query(SZ + tin[b], SZ + tin[b] + 1,
                push, [&](int ind) { cur += t[ind]; });
            SegmentTree::update(SZ + tin[b], SZ + tin[b] + 1,
                [&](int ind) { apply(ind, -cur); }, pull);
        } else {
            SegmentTree::update(SZ + tin[a], SZ + tout[a],
                [&](int ind) { apply(ind, b); }, pull);
        }
    }
    for (int i = 0; i < timer; i++) {
        SegmentTree::forParents(SZ + tin[i], false, push);
        cout << t[SZ + tin[i]] << " \n"[i == timer - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * Answer the queries offline. Precalculate
 * the Euler tours of the tree. When performing
 * query 1, all you need to do is invalidate all previous
 * range additions by setting this current location to 0.
 * For query 2, just range add to the entire subtree.
*/