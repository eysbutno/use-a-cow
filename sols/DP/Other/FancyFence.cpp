#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;
ll expo(ll x, ll n, ll m = MOD) {
    ll res = 1; x %= m;
    for (; n; n >>= 1, x = (x * x) % m) {
        if (n & 1) res = (res * x) % m;
    }
    return res;
}
void solve() {
    int n; cin >> n;
    vector<array<int, 2>> rect(n + 1);
    rect[0] = {0, 0}; // dummy index
    for (int j = 0; j < 2; j++) {
        for (int i = 1; i <= n; i++) {
            cin >> rect[i][j];
        }
    }
    vector<ll> pf(n + 1);
    for (int i = 1; i <= n; i++) {
        pf[i] = (pf[i - 1] + rect[i][1]) % MOD;
    }
    auto add = [&](ll &x, ll y) -> void {
        x += y, x = (x % MOD) + (x < 0) * MOD;
    };
    auto mult = [&](ll x, ll y) -> ll {
        return (x * y) % MOD;
    };
    const ll inv = expo(2, MOD - 2);
    auto binom = [&](ll x) -> ll {
        // returns: x choose 2
        return ((x * (x - 1) % MOD) * inv) % MOD;
    };
    vector<ll> dp(n + 1);
    stack<int> st({0});
    ll result = 0;
    for (int i = 1; i <= n; i++) {
        auto [h, w] = rect[i];
        while (!st.empty() && rect[st.top()][0] >= h) {
            st.pop();
        }
        ll inRect = mult(binom(h + 1), binom(w + 1));
        ll ok = (pf[i - 1] - pf[st.top()] + MOD) % MOD;
        ll partial = mult(mult(w, ok), binom(h + 1));
        ll outside = mult(dp[st.top()], w);
        add(result, (inRect + partial + outside) % MOD);
        dp[i] = dp[st.top()] + mult(ok + w, binom(h + 1));
        dp[i] %= MOD, st.push(i);
    }
    cout << result << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * A. Fancy Fence (CEOI)
 * The idea is to add each section in one at a time,
 * and for each fence, calculate how many beautiful rectangles
 * with an endpoint inside this current section.
*/