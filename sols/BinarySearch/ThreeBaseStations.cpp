#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    int n; cin >> n;
    vector<ll> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        x[i] *= 2;
    }
    sort(begin(x), end(x));
    auto check = [&](int mid) {
        ll prev = -2e9, cnt = 0;
        for (ll i : x) {
            if (prev < i) {
                prev = i + 2 * mid;
                ++cnt;
            }
        }
        return cnt <= 3;
    };
    ll low = 0, high = 2e9;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    if (low % 2 == 0) cout << (low / 2) << '\n';
    else cout << (low / 2) << ".5" << '\n';
    vector<ll> coords;
    ll prev = -2e9;
    for (ll i : x) {
        if (prev < i) {
            prev = i + 2 * low;
            coords.pb(i + low);
        }
    }
    while (size(coords) < 3) {
        coords.pb(coords.back());
    }
    for (ll i : coords) {
        if (i % 2 == 0) cout << (i / 2);
        else cout << (i / 2) << ".5";
        cout << ' ';
    }
}
/**
 * Binary search the distance.
 * Note: if you just multiply each
 * coordinate by two, and then
 * divide everything later, you 
 * don't need to worry about yucky
 * decimal precision stuff.
*/