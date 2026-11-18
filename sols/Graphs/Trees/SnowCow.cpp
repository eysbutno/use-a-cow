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
    template <typename F>
    void forParents(int p, bool dir, F f) {
        const auto lvls = log2(p);
        for (auto i = 1; i <= lvls; ++i) {
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
    int n, q;
    cin >> n >> q;
    vector<vector<int>> adj(n); 
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[--u].push_back(--v);
        adj[v].push_back(u);
    }
    vector<int> tin(n), tout(n);
    int timer = 0;
    auto tour = [&](int u, int p, auto&& tour) -> void {
        tin[u] = timer++;
        for (int v : adj[u]) if (v != p) {
            tour(v, u, tour);
        }
        tout[u] = timer;
    }; tour(0, -1, tour);
    vector<array<ll, 2>> t(n << 1);
    vector<int> lz(n);
    const auto apply = [&](int idx, int amt) -> void {
        t[idx][0] += 1LL * amt * t[idx][1];
        if (idx < n) lz[idx] += amt;
    };
    const auto pull = [&](int idx) -> void {
        t[idx][0] = t[idx << 1][0] + t[idx << 1 | 1][0];
        t[idx][0] += 1LL * lz[idx] * t[idx][1];
    };
    const auto push = [&](int idx) -> void {
        apply(idx << 1, lz[idx]);
        apply(idx << 1 | 1, lz[idx]);
        lz[idx] = 0;
    };
    for (int i = 0; i < n; i++) {
        t[n + i][1] = 1;
    }
    for (int i = n - 1; i >= 0; i--) {
        t[i][1] = t[i << 1][1] + t[i << 1 | 1][1];
    }
    map<int, set<pii>> ranges;
    auto update = [&]() -> void {
        int x, c; cin >> x >> c; --x;
        auto it = ranges[c].upper_bound({tin[x], -1});
        if (it != begin(ranges[c]) && (*prev(it))[1] >= tout[x]) {
            return;
        }
        while (it != end(ranges[c]) && (*it)[0] < tout[x]) {
            int lf = (*it)[0], rt = (*it)[1];
            SegmentTree::update(n + lf, n + rt, 
                [&](int ind) { apply(ind, -1); }, pull);
            it = ranges[c].erase(it);
        }
        ranges[c].insert({tin[x], tout[x]});
        SegmentTree::update(n + tin[x], n + tout[x], 
                [&](int ind) { apply(ind, 1); }, pull);
    };
    auto query = [&]() -> void {
        int x; cin >> x; --x;
        ll sum = 0;
        SegmentTree::query(n + tin[x], n + tout[x], push,
            [&](int ind) { sum += t[ind][0]; });
        cout << sum << "\n";
    };
    while (q--) {
        int t; cin >> t;
        (t == 1) ? update() : query();
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("snowcow.in", "r", stdin);
    freopen("snowcow.out", "w", stdout);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Every time you splash color onto a subtree,
 * you essentially add 1 to the # of unique colors,
 * for every subtree node. However, to prevent overcounting,
 * you need to do two things:
 * 1. Check if any parent nodes were colored with the same color.
 * If so, ignore this current update.
 * 2. Undo the range additions from "lower level" nodes with the same
 * color.
 * 
 * Then, to query, it's just standard lazy segtree query.
*/