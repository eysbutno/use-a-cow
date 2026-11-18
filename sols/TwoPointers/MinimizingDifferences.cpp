#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    ll n, k; cin >> n >> k;
    vector<ll> a(n);
    for (ll& i : a) cin >> i;
    sort(begin(a), end(a));
    ll l = 0, r = n - 1,
        c1 = a[0], c2 = a[n - 1];
    while (l < r && k > 0) {
        ll d1 = l + 1, d2 = n - r;
        if (d1 < d2) {
            ll dx = a[l + 1] - a[l];
            if (dx > k / d1) {
                c1 += k / d1;
                break;
            } else {
                c1 += dx;
                k -= dx * d1;
                ++l;
            }
        } else {
            ll dx = a[r] - a[r - 1];
            if (dx > k / d2) {
                c2 -= k / d2;
                break;
            } else {
                c2 -= dx;
                k -= dx * d2;
                --r;
            }
        }
    }
    cout << c2 - c1 << '\n';
}