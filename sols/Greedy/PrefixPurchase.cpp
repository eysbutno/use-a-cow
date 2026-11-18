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
    vector<int> c(n);
    for (int &i : c) {
        cin >> i;
    }
    vector<int> sf(n);
    sf[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        sf[i] = c[i] < c[sf[i + 1]] ? i : sf[i + 1];
    }
    int k; cin >> k;
    vector<int> res(n);
    res[sf[0]] += k / c[sf[0]];
    k %= c[sf[0]];
    int ptr = sf[0] + 1;
    while (ptr < n) {
        int dx = c[sf[ptr]] - c[ptr - 1];
        int rep = min(res[ptr - 1], k / dx);
        if (rep == 0) break;
        res[ptr - 1] -= rep;
        res[sf[ptr]] += rep;
        k -= dx * rep;
        ptr = sf[ptr] + 1;
    }
    for (int i = n - 2; i >= 0; i--) {
        res[i] += res[i + 1];
    }
    for (int i = 0; i < n; i++) {
        cout << res[i] << " \n"[i == n - 1];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * D. Prefix Purchase (CF)
 * All of our choices will be on some suffix minima, for
 * obvious reasons. Let's say we bought the cheapest prefix
 * increment, and have some amount left over. Obviously, we don't
 * want to waste these leftover coins. So, try to replace as many 
 * as possible with the next suffix minima. And repeat.
*/