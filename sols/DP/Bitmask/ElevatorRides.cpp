#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define mp(x, y) make_pair(x, y)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

pii dp[1 << 20];
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
int main() {
    int n, x; cin >> n >> x;
    vector<int> w(n);
    for (int& i : w) {
        cin >> i;
    }
    for (int i = 1; i < (1 << n); i++) {
        dp[i] = {n + 1, x + 1};
    }
    for (int i = 1; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            int bit = 1 << j;
            if (!(i & bit)) continue;
            auto [c, u] = dp[i ^ bit];
            if (u + w[j] > x) {
                ++c, u = w[j];
            } else {
                u += w[j];
            }
            smin(dp[i], mp(c, u));
        }
    }
    if (dp[(1 << n) - 1].s) {
        ++dp[(1 << n) - 1].f;
    }
    cout << dp[(1 << n) - 1].f;
}
/**
 * TASK: Elevator Rides.
 * At any given moment, we need to keep
 * track of how many elevators have been
 * used, and the current weight of the elevator.
 * 
 * For each subset, we just keep track of the last
 * person added, cuz that's all you need to do 
 * to get the answer.
*/