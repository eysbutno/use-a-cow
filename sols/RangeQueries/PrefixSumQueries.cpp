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
template <typename T> class SegmentTree {
    private:
        const T DEF = {0, 0};
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        SegmentTree(vector<T> &arr) {
            len = (int) arr.size();
            t = vector<T>(len * 2, DEF);
            for (int i = 0; i < len; i++) {
                t[i + len] = arr[i];
            }
            for (int i = len - 1; i >= 1; i--) {
                t[i] = join(t[i << 1], t[i << 1 | 1]);
            }
        }
        SegmentTree() {}
        T join(T a, T b) {
            return {a[0] + b[0], max(a[1], a[0] + b[1])};
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
            return t[idx + len];
        }
};
void solve() {
    int n, q; cin >> n >> q;
    SegmentTree<array<ll, 2>> st(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        st.set(i, {x, x});
    }
    while (q--) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            st.set(--x, {y, y});
        } else {
            cout << st.qry(--x, y)[1] << "\n";
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * CSES - Prefix Sum Queries.
 * Maintain a PURQ segment tree, with
 * each node storing sum and max prefix.
*/