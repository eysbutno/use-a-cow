#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
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
    template<typename F> 
    void forParents(int p, bool dir, F f) {
        const int lvls = log2(p);
        for (int i = 1; i <= lvls; ++i) {
            f(p >> (!dir ? lvls - i + 1 : i));
        }
    }
}
const int ADD = 1e6;
using Data = array<ll, 2>;
void solve() {
    int n; cin >> n;
    vector<array<int, 4>> eoi;
    eoi.reserve(2 * n);
    for (int i = 0; i < n; i++) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        x0 += ADD, y0 += ADD;
		x1 += ADD, y1 += ADD;
        eoi.push_back({x0, y0, y1, 1});
        eoi.push_back({x1, y0, y1, -1});
    }
    const int sz = 2e6 + 1;
    vector<Data> t(sz << 1);
    vector<ll> lz(sz);
    for (int i = 0; i < sz; i++) {
        t[sz + i][1] = 1;
    }
    for (int i = sz - 1; i >= 1; i--) {
        t[i][1] = t[i << 1][1] + t[i << 1 | 1][1];
    }
    auto join = [&](Data a, Data b) -> Data {
        if (a[0] < b[0]) return a;
        if (b[0] < a[0]) return b;
        return {a[0], a[1] + b[1]};
    };
    auto apply = [&](int idx, int amt) -> void {
        t[idx][0] += amt;
        if (idx < sz) lz[idx] += amt;
    };
    auto upd = [&](int l, int r, int v) -> void {
        SegmentTree::forRange(sz + l, sz + r,
            [&](int ind) { apply(ind, v); });
        for (int x : {l, r - 1}) {
            SegmentTree::forParents(sz + x, true, [&](int ind) {
                t[ind] = join(t[ind << 1], t[ind << 1 | 1]);
                t[ind][0] += lz[ind];
            });
        }
    };
    auto qry = [&]() -> int {
        Data cur = {0, 0};
        for (int x : {0, sz - 1}) {
            SegmentTree::forParents(sz + x, false, [&](int ind) {
                apply(ind << 1, lz[ind]);
                apply(ind << 1 | 1, lz[ind]);
                lz[ind] = 0;
            });
        }
        SegmentTree::forRange(sz, sz * 2, 
            [&](int ind) { cur = join(cur, t[ind]); });
        return sz - cur[1];
    };
    sort(all(eoi));
    ll res = 0;
    upd(eoi[0][1], eoi[0][2], 1);
    for (int i = 1; i < 2 * n; i++) {
        res += 1LL * qry() * (eoi[i][0] - eoi[i - 1][0]);
        upd(eoi[i][1], eoi[i][2], eoi[i][3]);
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Do a line sweep. Maintain a range add,
 * {max, max_occ} segment tree....
*/