#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
template<class T> class FenwickTree {
    private:
        int sz; vector<T> arr;
    public:
        FenwickTree(int n) {
            sz = n + 1;
            arr.resize(n + 1);
        }
        // FenwickTree() {} // empty init
        T prefix(int idx) {
            T tot = 0;
            for (++idx; idx >= 1; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < sz; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<int> a(n), pos(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i], pos[a[i]] = i;
    }
    vector<vector<array<int, 2>>> tests(n);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        tests[--l].push_back({--r, i});
    }
    vector<ll> res(q), dp(n + 1);
    /**
     * dp[i] = # of possible sequences, if
     *         left endpoint = what we're iterating on,
     *         and right endpoint is pos[i] (with a[pos[i]] = i)
    */
    FenwickTree<ll> ft(n + 1);
    /**
     * ft's index at i = # of subsequences,
     * given that they end at i, and the left
     * endpoint is valid (b/c sweeping R -> L)
    */
    for (int i = n - 1; i >= 0; i--) {
        // now consider a[x] in our calculations.
        dp[a[i]] = 1; // empty is a valid option.
        for (int j = a[i]; j <= n; j += a[i]) {
            // check that this value is after i.
            if (pos[j] < i) continue;
            // DP transition to add to more sequences.
            for (int k = j * 2; k <= n; k += j) {
                // need to make sure pos[j] < pos[k].
                // pos[k] is ok for pos[j]-ending sequences.
                if (pos[j] < pos[k]) dp[k] += dp[j];
            }
        }
        for (int j = a[i]; j <= n; j += a[i]) {
            // clear DP array & update Fenwick tree
            ft.update(pos[j], dp[j]), dp[j] = 0;
        }
        for (auto [r, id] : tests[i]) {
            res[id] = ft.query(i, r);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << " \n"[i == q - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}