#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

template<class T> class FT {
    private:
        int sz;
        vector<T> arr;
    public:
        FT(int n) {
            sz = n + 1;
            arr.resize(n + 1);
        }
        T prefix(int idx) {
            ++idx; 
            T tot = 0;
            while (idx >= 1) {
                tot += arr[idx];
                idx -= idx & -idx;
            }
            return tot;
        }
        T query(int l, int r) {
            return prefix(r) - prefix(l - 1);
        }
        void update(int idx, T dx) {
            ++idx;
            while (idx <= sz) {
                arr[idx] += dx;
                idx += idx & -idx;
            }
        }
};
ll solve(vector<int>& a, 
    vector<int>& b, int n) {
    vector<int> m1(n), m2(n);
    for (int i = 0; i < n; i++) {
        m1[a[i]] = i, m2[b[i]] = i;
    }
    FT<int> bit(n + 5);
    ll res = 0;
    for (int i = 0; i < n; i++) {
        res += bit.query(m1[b[i]], n - 1);
        bit.update(m1[b[i]], 1);
    }
    ll cur = res;
    for (int i = n - 1; i >= 0; i--) {
        cur += 2 * m2[a[i]] - (n - 1);
        ckmin(res, cur);
    } 
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
    int n; cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i], --a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i], --b[i];
    }
    cout << min(solve(a, b, n),
        solve(b, a, n)) << '\n';
}
/**
 * Problem: Mincross.
 * Note: # of pairs = number of
 * inversions. To count the initial
 * inversions, you use the mapped
 * indexes.
 * 
 * For any rotation, the answer
 * will change by P * 2 - (N + 1),
 * where P is the final position.
 * 
 * Justification:
 * Because said cow is initially 
 * at the end of the line, it 
 * contributes N - P inversions.
 * 
 * When the cow moves to the start
 * of the line, it'll contribute
 * P - 1 inversions.
*/