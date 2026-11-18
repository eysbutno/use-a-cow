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
void solve() {
    int n, q; 
    cin >> n >> q;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    const int MX = 1e5;
    vector<int> pdiv(MX + 1);
    iota(all(pdiv), 0);
    for (int i = 2; i <= MX; i++) {
        if (pdiv[i] != i) continue;
        for (int j = i * 2; j <= MX; j += i) {
            pdiv[j] = i;
        }
    }
    const int LOG = 32 - __builtin_clz(n);
    vector lift(LOG, vector(n + 1, n));
    vector<int> lst(MX + 1, n + 1); // last occ of pdiv
    for (int i = n - 1; i >= 0; i--) {
        int idx = lift[0][i + 1];
        while (a[i] > 1) {
            int p = pdiv[a[i]];
            while (a[i] % p == 0) {
                a[i] /= p;
            }
            smin(idx, lst[p]);
            lst[p] = i;
        }
        lift[0][i] = idx;
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 0; j < n; j++) {
            lift[i][j] = lift[i - 1][lift[i - 1][j]];
        }
    }
    auto qry = [&](int l, int r) -> int {
        int cnt = 0;
        for (int i = LOG - 1; i >= 0; i--) {
            if (lift[i][l] <= r) {
                cnt += (1 << i);
                l = lift[i][l];
            }
        }
        return cnt + 1;
    };
    while (q--) {
        int l, r; cin >> l >> r;
        cout << qry(--l, --r) << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * D. Cut (Codeforces)
 * LCM = Product essentially means that for each prime P,
 * max(expo_p) = sum(expo_p) for every number in a range.
 * Thus, every prime can only divide ONE number in the range...
 * Because of this, every number in a range strictly adds more constraints,
 * so making every range as long as possible is obviously optimal.
*/