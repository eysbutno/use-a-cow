#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) (x).begin(), (x).end()
#define sz(x) (int) (x).size()

#ifdef LOCAL
#include "../src/debug.hpp"
#else
#define debug(...) 420
#endif
// g++ -DLOCAL -Wall Practice.cpp -o bin

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    array<int, 3> a = {0, 0, 0};
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x - 1]++;
    }
    using ld = long double;
    vector dp(n + 2, vector(n + 2, vector(n + 2, (ld) 0)));
    auto memo = [&](int a, int b, int c, auto&& memo) -> ld {
        if (a < 0 || b < 0 || c < 0) return 0;
        if (!a && !b && !c) return 0;
        if (dp[a][b][c] > 0) {
            return dp[a][b][c];
        }
        int rem = a + b + c;
        ld val = n + a * memo(a - 1, b, c, memo)
               + b * memo(a + 1, b - 1, c, memo)
               + c * memo(a, b + 1, c - 1, memo);
        return dp[a][b][c] = val / rem;
    };
    cout << fixed << setprecision(20);
    cout << memo(a[0], a[1], a[2], memo) << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * f(x, y, z) = expected value of time if you eat
 * x 1 sushi plates, y 2 sushi plates, and z 3 sushi plates.
*/