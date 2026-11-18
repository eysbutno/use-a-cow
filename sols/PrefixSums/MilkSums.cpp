#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<ll> a(n), v(n), p(n);
    for (ll &i : a) cin >> i;
    iota(begin(v), end(v), 0);
    sort(begin(v), end(v), [&](int x, int y) {
        return a[x] < a[y];
    });
    for (int i = 0; i < n; i++) {
        p[v[i]] = i;
    }
    sort(begin(a), end(a));
    ll total = 0; vector<ll> pf(n + 1);
    for (int i = 1; i <= n; i++) {
        pf[i] = pf[i - 1] + a[i - 1];
        total += a[i - 1] * i;
    }
    int q; cin >> q;
    while (q--) {
        ll idx, rep; 
        cin >> idx >> rep; idx--;
        idx = p[idx];
        ll loc = lower_bound(
            begin(a), end(a), rep) 
            - begin(a) - (bool)(rep > a[idx]);
        ll ans = total + (loc + 1) * rep - (idx + 1) * a[idx];
        if (loc < idx) {
            ans += (pf[idx] - pf[loc]);
        } else {
            ans -= pf[loc + 1] - pf[idx + 1];
        }
        cout << ans << "\n";
    }
}