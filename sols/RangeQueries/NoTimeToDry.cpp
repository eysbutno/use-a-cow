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
template<class T> class FenwickTree {
    private:
        int n; vector<T> arr;
    public:
        FenwickTree(int _n) : n(_n + 1) {
            arr.resize(n);
        }
        T prefix(int idx) { // [0, idx] sum
            T tot = 0;
            for (++idx; idx >= 1; idx -= idx & -idx) {
                tot += arr[idx];
            }
            return tot;
        }
        T query(int l, int r) { // [l, r] sum
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            for (++idx; idx < n; idx += idx & -idx) {
                arr[idx] += dx;
            }
        }
};
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    vector<vector<pii>> tests(n);
    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        tests[--r].push_back({--l, i});
    }
    stack<int> stk;
    vector<int> res(q);
    FenwickTree<int> ft(n);
    for (int i = 0; i < n; i++) {
        while (!stk.empty() && a[stk.top()] > a[i]) {
            stk.pop();
        }
        if (!stk.empty() && a[stk.top()] == a[i]) {
            ft.update(stk.top(), -1);
            stk.pop();
        }
        stk.push(i);
        ft.update(i, 1);
        for (auto &[j, idx] : tests[i]) {
            res[idx] = ft.query(j, i);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << res[i] << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * 1. No Time To Dry (USACO Plat)
 * Sweep from left to right. Note that for each "coloring",
 * we only care about the right endpoint. So, we use a BIT
 * to query on all the right endpoints within our range.
*/