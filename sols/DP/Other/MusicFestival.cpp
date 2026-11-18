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
    int n; cin >> n;
    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int k, mx = 0; cin >> k;
        while (k--) {
            int x; cin >> x;
            if (smax(mx, x)) {
                a[i].push_back(x);
            }
        }
    }
    sort(all(a), [&](auto &i, auto &j) {
        return i.back() < j.back();
    });
    map<int, int> dp = {{0, 0}};
    for (int i = 0; i < n; i++) {
        int z = sz(a[i]), best = 0;
        for (int j = 0; j < z; j++) {
            auto it = prev(dp.lower_bound(a[i][j]));
            smax(best, (it -> second) + z - j);
        }
        auto prv = prev(dp.upper_bound(a[i][z - 1]));
        if (prv -> second < best) {
            dp[a[i][z - 1]] = best;
            prv = dp.upper_bound(a[i][z - 1]);
            while (prv != end(dp) && prv -> second <= best) {
                prv = dp.erase(prv);
            }
        }
    }
    cout << (rbegin(dp) -> second) << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * 1801C - Music Festival (CF)
 * Basically, the question is asking how many
 * times you can change the prefix maximum.
 * Because of this, we obviously only need to store
 * the prefix maximums. Then, sort the albums by 
 * their maximum.
 * 
 * After that, we can have a naive DP. This DP is just
 * maintaining the most impressions we can gain from having
 * an ending prefix maxima of some value. Obviously, this DP
 * must be monotonically increasing. So, yeah.
*/