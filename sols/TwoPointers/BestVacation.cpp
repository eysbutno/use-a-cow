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
    int n; ll x; 
    cin >> n >> x;
    vector<int> d(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> d[i], d[i + n] = d[i];
    }
    int ptr = 2 * n - 1;
    ll best = 0, days = 0, hugs = 0;
    const auto f = [&](int x) -> ll {
        return 1LL * x * (x + 1) / 2;
    };
    for (int i = 2 * n - 1; i >= 0; i--) {
        smin(ptr, i);
        while (ptr >= 0 && days + d[ptr] <= x) {
            hugs += f(d[ptr]), days += d[ptr], --ptr;
        }
        ll rem = 0;
        if (ptr >= 0 && x - days > 0) {
            rem = f(d[ptr]) - f(d[ptr] - (x - days));
        }
        smax(best, rem + hugs);
        if (ptr < i) hugs -= f(d[i]), days -= d[i];
    }
    cout << best << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * Claim: The end of some optimal subsegment
 * will be at the exact end of some month.
 * Proof: Moving this subsegment to the right, for
 * obvious reasons, is suboptimal. The only possibility
 * that moving to the left is optimal, is if moving to the left
 * accesses the last day of some month with length greater than
 * this one. However, if that is the case, then an earlier end point
 * will cover that later month. Thus, having the end of a subsegment
 * being the end of some trip will strictly construct an optimal answer.
*/