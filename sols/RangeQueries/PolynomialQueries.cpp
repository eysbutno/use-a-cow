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
        return 1 << SegmentTree::log2(x * 2 - 1);
    }
    template <typename F>
    void forParents(int p, bool dir, F f) {
        const int lvls = log2(p);
        for (int i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
    template <typename F>
    void forRangeOrdered(int lf, int rt, bool dir, F f) {
        auto base = !dir ? lf - 1 : rt;
        const int mask = (1 << log2((lf - 1) ^ rt)) - 1;
        const int offset = !dir ? 1 : -1;
        int node = (!dir ? -lf : rt) & mask;
        while (node) {
            const int bit = __builtin_ctz(node);
            f((base >> bit) + offset);
            node ^= 1 << bit;
        }
        base = dir ? lf - 1 : rt;
        node = (dir ? -lf : rt) & mask;
        while (node) {
            const int bit = log2(node);
            f((base >> bit) - offset);
            node ^= 1 << bit;
        }
    }
    template<class T, class U>
    void update(int l, int r, T apply, U pull) {
        forRangeOrdered(l, r, false, apply);
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
    const int sz = SegmentTree::size(n);
    vector<ll> t(sz << 1);
    vector<int> itvs(sz << 1);
    vector<array<ll, 2>> lz(sz);
    for (int i = 0; i < n; i++) {
        cin >> t[sz + i];
    }
    fill(begin(itvs) + sz, begin(itvs) + sz + n, 1);
    const auto changes = [&](array<ll, 2> v, ll sub) -> ll {
        return v[0] * sub + v[1] * sub * (sub + 1) / 2;
    };
    const auto pull = [&](int idx) -> void {
        t[idx] = t[idx << 1] + t[idx << 1 | 1] + changes(lz[idx], itvs[idx]);
    };
    for (int i = sz - 1; i >= 1; i--) {
        pull(i), itvs[i] = itvs[i << 1] + itvs[i << 1 | 1];
    }
    vector<int> times(sz);
    const auto apply = [&](int idx, array<ll, 2> v, int cnt) {
        t[idx] += changes(v, itvs[idx]);
        if (idx < sz) {
            lz[idx][0] += v[0];
            lz[idx][1] += v[1];
            times[idx] += cnt;
        }
    };
    const auto upd = [&](int l, int r) -> void {
        int reached = 0;
        SegmentTree::update(sz + l, sz + r + 1, [&](int ind) {
            apply(ind, {reached, 1}, 1), reached += itvs[ind];
        }, pull);
    };
    const auto qry = [&](int l, int r) -> void {
        const auto push = [&](int idx) -> void {
            apply(idx << 1, lz[idx], times[idx]);
            lz[idx][0] += times[idx] * itvs[idx << 1];
            apply(idx << 1 | 1, lz[idx], times[idx]);
            lz[idx] = {0, 0}, times[idx] = 0;
        };
        ll res = 0;
        SegmentTree::query(sz + l, sz + r + 1, 
            push, [&](int ind) { res += t[ind]; });
        cout << res << "\n";
    };
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l, --r;
        (t > 1) ? qry(l, r) : upd(l, r);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Polynomial Queries - CSES
 * Suppose we range increase [a, b], and are at
 * a segment [c, d], where [c, d] is contained in [a, b].
 * Then, we add (c - a + 1) + (c - a + 2).... + (d - a + 1), to
 * this segment. Interestingly, this expression is the same as
 * (c - a) * (d - c + 1) + 1 + 2 + 3.... + (d - c + 1).
 * Now we can do lazy propagation, as we just need to track
 * how many times to add 1 + 2 + 3.... + (d - c + 1), and the
 * sum of all (c - a)...
*/