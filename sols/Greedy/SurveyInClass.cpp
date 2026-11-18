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
    int n, m;
    cin >> n >> m;
    vector<pii> t(n);
    int l = -1, r = m, len = m + 1;
    for (auto &[f, s] : t) {
        cin >> f >> s; --f, --s;
        smax(l, f), smin(r, s);
        smin(len, s - f + 1);
    }
    int res = 0;
    for (auto [f, s] : t) {
        int overlap = min({s - l + 1, r - f + 1, len});
        smax(res, s - f + 1 - max(overlap, 0));
    }
    cout << 2 * res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * D. Survey In Class (Codeforces)
 * For obvious reasons, we will use the entire segment
 * of our chosen "best" student.
 * 
 * There are only a few ways a segment can intersect this current one:
 * 1. Left endpoint outside, right endpoint inside.
 * 2. Left endpoint inside, right endpoint outside.
 * 3. Both endpoints inside.
 * 4. Does not intersect.
*/