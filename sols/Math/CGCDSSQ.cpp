#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    map<int, ll> res, occ;
    for (int i = 0; i < n; i++) {
        map<int, ll> occ_t;
        for (auto &[k, v] : occ) {
            occ_t[__gcd(k, a[i])] += v;
        }
        occ_t[a[i]]++;
        for (auto &[k, v] : occ_t) {
            res[k] += v;
        }
        occ = occ_t;
    }
    int q; cin >> q;
    while (q--) {
        int x; cin >> x;
        cout << res[x] << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * 1. At most O(n log(n)) distinct GCDs, because for 
 *    a given left endpoint there are only O(log(n)) distinct GCDs.
 * With this fact, we can sweep left to right and keep track of each
 * possible GCD, & the # of such left endpoints. Kinda.
*/