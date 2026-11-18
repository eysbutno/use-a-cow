#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

#ifdef LOCAL
#include "../src/debug.hpp"
#else
#define debug(...) 7
#endif

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
    const int b = (int) (sqrt(n));
    vector sf1(b, vector(n, 0LL));
    vector sf2(b, vector(n, 0LL));
    for (int i = 1; i < b; i++) {
        for (int j = n - 1; j >= 0; j--) {
            if (i + j >= n) {
                sf1[i][j] = sf2[i][j] = a[j];
            } else {
                sf1[i][j] = a[j] + sf1[i][i + j];
                sf2[i][j] = sf1[i][j] + sf2[i][i + j];
            }
        }
    }
    auto qry = [&](int s, int d, int k) -> ll {
        ll res = 0;
        if (d >= b) {
            for (int i = 0; i < k; i++) {
                res += 1LL * (i + 1) * a[s + i * d];
            }
        } else {
            res = sf2[d][s];
            int r = s + k * d;
            if (r < n) {
                res -= sf2[d][r] + sf1[d][r] * k;
            }
        }
        return res;
    };
    while (q--) {
        int s, d, k;
        cin >> s >> d >> k;
        cout << qry(--s, d, k) << " \n"[q < 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * Use sqrt decomp ideas. Essentially,
 * if d is sufficiently big, then we can
 * obviously just directly calculate it. Otherwise,
 * we precomp it.
*/