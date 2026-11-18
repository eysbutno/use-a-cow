#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int n, m; cin >> n >> m;
    vector<ll> cities(n);
    set<ll> towers;
    for (ll &i : cities) {
        cin >> i;
    }
    while (m--) {
        ll num; cin >> num;
        towers.insert(num);
    }
    ll ans = 0;
    for (ll i : cities) {
        auto ptr = towers.lower_bound(i);
        ll dist = 2e9;
        if (ptr != end(towers)) {
            dist = min(dist, *ptr - i);
        }
        if (ptr != begin(towers)) {
            --ptr;
            dist = min(dist, i - *ptr);
        }
        ans = max(dist, ans);
    }
    cout << ans << "\n";
}