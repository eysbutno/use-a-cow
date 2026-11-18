#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first
#define s second

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll g, n; cin >> g >> n;
    map<ll, pair<ll, ll>> grazings;
    while (g--) {
        ll x, y, t; cin >> x >> y >> t;
        grazings[t] = {x, y};
    }
    ll ans = 0;
    auto works = [&](ll x1, ll y1, ll x2, ll y2, ll t1, ll t2) {
        ll t = (t1 - t2) * (t1 - t2);
        ll hd = (x1 - x2) * (x1 - x2);
        ll vd = (y1 - y2) * (y1 - y2);
        return t < hd + vd;
    };
    while (n--) {
        ll x, y, t; cin >> x >> y >> t;
        auto ptr = grazings.lower_bound(t);
        bool sus = true;
        if (ptr != end(grazings)) {           
            ll key = ptr -> first;
            auto loc = ptr -> second;
            if (works(x, y, loc.f, loc.s, key, t)) sus = 0;
        }
        if (ptr != begin(grazings)) {
            --ptr; ll key = ptr -> first;
            auto loc = ptr -> second;
            if (works(x, y, loc.f, loc.s, key, t)) sus = 0;
        }
        ans += !sus;
    }
    cout << ans << "\n";
}
/*
Type: Binary Search, Sorted Set
Algorithm:
It's (essentially) guaranteed that it's possible
for a cow to eat all the grass (w/o the alibi), so 
no need to worry about that. In order to find a cow innocent or guilty,
you want to find the two most recent (before and after the alibi)
grazings and see if it's possible for that cow to have done it.
NOTE TO SELF: when working with big numbers, always use long long to be safe.
*/