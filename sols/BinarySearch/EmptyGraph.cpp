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
    int n, k; 
    cin >> n >> k;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    const int INF = 1e9;
    auto fn = [&](int x) -> bool {
        auto cpy = a;
        int upd = k;
        for (int &i : cpy) {
            if (i * 2 < x) {
                i = INF, --upd;
            }
        }
        if (upd < 0) return false;
        if (upd >= 2) return true;
        for (int i = 1; i < n; i++) {
            if (min(cpy[i - 1], cpy[i]) >= x) {
                return true;
            } else if (upd && max(cpy[i - 1], cpy[i]) >= x) {
                return true;
            }
        }
        return false;
    };
    int lo = 0, hi = INF;
    while (lo < hi) {
        int mi = (lo + hi + 1) >> 1;
        fn(mi) ? lo = mi : hi = mi - 1;
    }
    cout << lo << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * Claim: Diameter is between a_i and a_i+1
 * Proof: There are two optimal SPs: either
 * go to min({a_i}), then to your next destination,
 * or to just go directly. a_i and a_i+1 has the least
 * flexibility; theirfore, it must be the worst.
 * 
 * Then, binary search on the answer.
*/