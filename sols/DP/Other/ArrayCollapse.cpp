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

const int MOD = 998244353;
void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (int& i : p) {
        cin >> i;
    }
    vector<ll> dps(n + 2), dpc(n);
    dps[n] = 1;
    stack<int> lst;
    for (int i = n - 1; i >= 0; i--) {
        while (!lst.empty() && p[lst.top()] > p[i]) {
            lst.pop();
        }
        int nxt = lst.empty() ? n : lst.top();
        lst.push(i);
        ll sum = (dps[i + 1] - dps[nxt + 1] + MOD) % MOD;
        if (nxt != n) {
            sum += dpc[nxt], sum %= MOD;
            dpc[i] = dpc[nxt] + dps[nxt] - dps[nxt + 1];
            dpc[i] %= MOD; if (dpc[i] < 0) dpc[i] += MOD;
        }
        dps[i] = sum + dps[i + 1], dps[i] %= MOD;
    }
    ll res = 0;
    int mn = 2e9;
    for (int i = 0; i < n; i++) {
        mn = min(mn, p[i]);
        if (mn == p[i]) {
            res += dps[i] - dps[i + 1], res %= MOD;
            if (res < 0) res += MOD;
        }
    }
    cout << res << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Array Collapse (CF).
 * Rephrase the problem to find the # of 
 * reachable subsequences.
 * 
 * Let dp[i] be the # of subsequences that
 * end on i, using the prefix i's elements.
 * Then, to transition, we need to consider the
 * following:
 * 1. Find the nearest lefthand element j, such that
 *    p[j] < p[i].
 * 2. Add the entire subsegment of dp in [i, j].
 * 3. Add the entire "chain" of dp[nxt[nxt[i]]...].
 * Step 3 is necessary because it is possible to
 * delete element j; you just need to consider the next 
 * leftmost element.
 * 
 * This is implemented R->L because it's easier like that.
*/