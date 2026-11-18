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
        const T DEF = 2e9;
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        T join(T a, T b) { return min(a, b); }
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
    int n, p;
    cin >> n >> p;
    vector<int> distinct;
    vector<array<int, 4>> eoi;
    eoi.reserve(p * 2), distinct.reserve(p * 2);
    for (int i = 0; i < p; i++) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        eoi.push_back({x0, y0, i, 0});
        eoi.push_back({x1, y1, i, 1});
        distinct.push_back(y0);
        distinct.push_back(y1);
    }
    sort(all(eoi)), sort(all(distinct));
    auto yIdx = [&](int y) -> int {
        return lower_bound(all(distinct), y) - begin(distinct);
    };
    SegmentTree<int> rmq(2 * p);
    rmq.set(0, 0);
    vector<int> res(p);
    for (auto [x, y, idx, type] : eoi) {
        if (type == 0) {
            res[idx] = x + y + rmq.qry(0, yIdx(y) + 1);
        } else if (res[idx] - x - y < rmq.get(yIdx(y))) {
            rmq.set(yIdx(y), res[idx] - x - y);
        }
    }
    cout << rmq.qry(0, 2 * p) + 2 * n << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Springboards (USACO Gold)
 * Idea is to sweep left to right, storing the maximum "savings"
 * at every y value as we sweep left to right. Then, we use segment tree RMQ.
*/