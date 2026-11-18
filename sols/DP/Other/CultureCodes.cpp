#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

const int MOD = 1e9 + 7;
int norm(ll cur) {
    cur %= MOD;
    if (cur < 0) cur += MOD;
    return cur;
}
template <class T> class SegmentTree {
    private:
        const T DEF = array<ll, 2>{(ll) 1e18, 0};
        int len; vector<T> t;
    public:
        SegmentTree(int len) : len(len),
            t(len * 2, DEF) {}
        SegmentTree() {} // for empty init
        T join(T a, T b) {
            if (a[0] == b[0]) {
                return {a[0], norm(a[1] + b[1])};
            }
            return min(a, b);
        }
        void set(int idx, T val) {
            t[idx += len] = val;
            for (; idx > 1; idx >>= 1) {
                t[idx / 2] = join(t[idx], t[idx ^ 1]);
            }
        }
        T qry(int l, int r) { // queries [l, r)
            T res = DEF;
            for (l += len, r += len; l < r; l >>= 1, r >>= 1) {
                if (l & 1) res = join(res, t[l++]);
                if (r & 1) res = join(res, t[--r]);
            }
            return res;
        }
        T get(int idx) {
            return qry(idx, idx + 1);
        }
};
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<array<int, 2>> a(n);
    // {inside, outside} volumes.
    for (int i = 0; i < n; i++) {
        cin >> a[i][1] >> a[i][0];
    }
    sort(all(a)); // to use lower_bound.
    SegmentTree<array<ll, 2>> st(n);
    for (int i = n - 1; i >= 0; i--) {
        int idx = lower_bound(begin(a) + i + 1, end(a),
                  array<int, 2>{a[i][1], -1}) - begin(a);
        if (idx < n) {
            auto res = st.qry(idx, n);
            res[0] -= a[i][1], res[0] += a[i][0];
            st.set(i, res);
        } else {
            st.set(i, {a[i][0], 1});
        }
    }
    int mn = 2e9;
    for (int i = 0; i < n; i++) {
        if (a[i][0] >= mn) {
            st.set(i, {(ll) 1e18, 0});
        }
        mn = min(mn, a[i][1]);
    }
    cout << st.qry(0, n)[1] << "\n";
}
/**
 * TASK: E. Culture Code (CF)
 * Key Points:
 * - Find # of sequences of dolls, such that
 *   no other doll can be added to the back.
 * - Each subsequence must have minimal space wasted.
 * - Note that inside volume is <= outside volume.
 * 
 * First, sort everything by inside volume, as each nested
 * ordering will now be a subsequence of the array.
 * dp[i] = (min waste, # of subsequences ending with i).
 * Then, we can add all the previous subsequences with 
 * a >= inside value than this doll's outside value. 
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/