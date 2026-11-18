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
template <typename T> class SegmentTree {
    private:
        const ll LINF = 1e18;
        const T DEF = {0, 0, 0, 0, 0, 0, 0};
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        SegmentTree() {} // empty init
        T join(T a, T b) {
            T res = DEF;
            res[0] = max(a[0], a[6] + b[0]);
            res[1] = min(a[1], a[6] + b[1]);
            res[2] = max(b[2], b[6] + a[2]);
            res[3] = min(b[3], b[6] + a[3]);
            res[4] = max({a[2] + b[0], a[4], b[4]});
            res[5] = min({a[3] + b[1], a[5], b[5]});
            res[6] = a[6] + b[6];
            return res;
        }
        void set(int idx, T val) { 
            for (t[idx += len] = val; idx >>= 1; ) {
                t[idx] = join(t[idx << 1], t[idx << 1 | 1]);
            }
        }
        T qry(int l, int r) { // queries [l, r)
            T resl = DEF, resr = DEF;
            for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
                if (l & 1) resl = join(resl, t[l++]);
                if (r & 1) resr = join(t[--r], resr);
            }
            return join(resl, resr);
        }
        T get(int idx) {
            return qry(idx, idx + 1);
        }
};
void solve() {
    int n, q; cin >> n >> q;
    SegmentTree<array<ll, 7>> segtree(n);
    auto init = [&](int v) -> array<ll, 7> {
        array<ll, 7> res;
        res[1] = res[3] = res[5] = min(0, v);
        res[0] = res[2] = res[4] = max(0, v);
        res[6] = v;
        return res;
    };
    for (int i = 0; i < n; i++) {
        int v; cin >> v;
        segtree.set(i, init(v));
    }
    auto qry = [&]() -> void {
        int k, x; cin >> k >> x;
        segtree.set(--k, init(x));
        array<ll, 7> res = segtree.qry(0, n);
        cout << res[4] << "\n";
    };
    while (q--) { qry(); }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Store best prefix, best sum, best subarray, and sum.
 * (I included some extra stuff b/c I was too lazy to rewrite)
*/