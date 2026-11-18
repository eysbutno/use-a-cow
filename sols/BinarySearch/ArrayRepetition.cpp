#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 
 
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int N = 1e5;
int t[N + 1], x[N + 1];
ll cur[N + 1];
void solve() {
    int n, q; cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> x[i];
        if (t[i] == 1) {
            cur[i] = cur[i - 1] + 1;   
        } else {
            if ((x[i] + 1) > 2e18 / cur[i - 1]) {
                cur[i] = 2e18;
            } else {
                cur[i] = cur[i - 1] * (x[i] + 1);
            }
        }
    }
    auto query = [&](ll q) {
        int pos = lower_bound(cur, cur + n + 1, q)
                - cur;
        // cout << cur[pos] << '\n';
        while (t[pos] != 1) {
            ll prv = cur[pos - 1];
            // cout << q << ' ' << prv << '\n';
            q = (q - 1) % prv + 1;
            pos = lower_bound(cur, cur + n + 1, q)
                - cur;
        }
        // once t[pos] is 1, that means
        // we reached the exact location
        return x[pos];
    };
    while (q--) {
        ll q; cin >> q;
        cout << query(q) << ' ';
    }
    cout << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Array Repetition.
 * OK, so I think in order to solve this problem,
 * you kind of need to be able to backtrack to map
 * the # to a previous state.
 * 
 * So, as a basis, I think you can start of by finding
 * the first "position" (in the sequence of N steps) where
 * sum >= the position. 
 * 
 * Then, to map the index to a number, we can perform the 
 * following: 
 * 
 * If the operation at this index is a repetition, then map
 * the index into the location in the previous array, mod
 * (previous size). Then, repeat. Otherwise, we have our answer.
 * 
 * NOTE: The size of the array CAN and WILL exceed the long long
 * limit. To fix this, set anything that can overflow to be 
 * some number bigger than 1e18.
*/