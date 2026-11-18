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
    int n; ll k;
    cin >> n >> k;
    vector<int> x(2 * n);
    for (int i = 0; i < n; i++) {
        cin >> x[i], x[i + n] = x[i];
    }
    const int LOG = 32 - __builtin_clz(n);
    vector lift(LOG, vector(2 * n + 1, 2 * n));
    int ptr = 0; ll sum = 0;
    for (int i = 0; i < 2 * n; i++) {
        while (ptr < 2 * n && sum + x[ptr] <= k) {
            sum += x[ptr], ++ptr;
        }
        lift[0][i] = ptr;
        sum -= x[i];
    }
    for (int i = 1; i < LOG; i++) {
        for (int j = 0; j < 2 * n; j++) {
            lift[i][j] = lift[i - 1][lift[i - 1][j]];
        }
    }
    int res = n;
    for (int i = 0; i < n; i++) {
        int idx = i, cur = 0;
        for (int j = LOG - 1; j >= 0; j--) {
            if (lift[j][idx] < i + n) {
                idx = lift[j][idx];
                cur += (1 << j);
            }
        }
        smin(res, cur + 1);
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Cyclic Array (CSES)
 * For each index, find the last index allowing for
 * a subarray of sum <= k. Then, binlift.
*/