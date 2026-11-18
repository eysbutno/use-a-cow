#include <bits/stdc++.h>
using namespace std;

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
array<int, 3> f[2001];
int dp[2001][4001];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, a, b; cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        int p, c, x; 
        cin >> p >> c >> x;
        f[i] = {p, c, x};
    }
    sort(f, f + n, [&](auto& x, auto& y) {
        return x[2] > y[2];
    });
    for (int i = 1; i <= n; i++) {
        auto [p, c, x] = f[i - 1];
        for (int j = 1; j <= a + b; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            int used = max(0, min(j - a, c * x));
            int price = c - (used / x);
            if (price <= min(a, j)) {
                smax(dp[i][j], dp[i - 1][j - (used + price)] + p);
            }
        }
    }
    cout << dp[n][a + b] << '\n';
}   
/**
 * TASK: Bribing Friends.
 * Observation 1:
 * For a given subset of cows, we
 * use the ice cream cones on the cow
 * with the smallest x_i.
 * 
 * Observation 2:
 * When adding cows in ascending order
 * of x_i, there are two possibilities:
 * 1. You are completely out of cones.
 * 2. Everything beforehand has a cost of 0.
 * 
 * Therefore, when adding each new cow in,
 * we only need to consider two states:
 * A. dp[0][i] = most you can use, if i
 *    cones are used and everything is 0.
 * B. dp[1][i] = most you can use, if you
 *    have ran out of cones and you've spent
 *    i moonies already.
*/