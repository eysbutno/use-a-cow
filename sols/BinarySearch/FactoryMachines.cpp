#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n, t; cin >> n >> t;
    ll low = 0, high = 1e18;
    vector<ll> machines(n);
    for (ll &i : machines) {
        cin >> i; high = min(high, i * t);
    }
    auto check = [&](ll mid) {
        ll made = t;
        for (ll i : machines) {
            made -= mid / i;
        }
        return made <= 0;
    };
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << "\n";
}