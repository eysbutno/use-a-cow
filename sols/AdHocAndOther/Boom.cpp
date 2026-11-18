#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const ll MOD = 1LL << 32;
int main() {
    string s; cin >> s;
    int n = s.length();
    s = " " + s;
    vector<int> c(n + 1), w(n + 1), o(n + 1);
    for (int i = 2; i <= n; i++) {
        c[i] = (c[i - 1] + (s[i - 1] == 'C')) % MOD;
    }
    for (int i = n - 1; i >= 1; i--) {
        w[i] = (w[i + 1] + (s[i + 1] == 'W')) % MOD;
    }
    vector<int> scw(n + 1), sw(n + 1), sc(n + 1);
    for (int i = 1; i <= n; i++) {
        int S = (s[i] == 'O');
        o[i] = (o[i - 1] + S) % MOD;
        scw[i] = (scw[i - 1] + S * c[i] * w[i]) % MOD;
        sw[i] = (sw[i - 1] + S * w[i]) % MOD;
        sc[i] = (sc[i - 1] + S * c[i]) % MOD;
    }
    auto calc = [&](int l, int r) {
        ll res = (scw[r] - scw[l - 1] - c[l] * 
            (sw[r] - sw[l - 1]) - w[r] * (sc[r] - sc[l - 1]) 
            + c[l] * w[r] * (o[r] - o[l - 1])) % MOD;
        if (res < 0) {
            res += MOD;
        }
        return res;
    };
    int q; cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << calc(l, r) << '\n';
    }
}
/**
 * Ans = sum l -> r ((s_i == 0) * 
 * (c[i] - c[l]) * (w[i] - w[r]))
 * 
 * Do some manipulation until you can
 * query in O(1).
*/