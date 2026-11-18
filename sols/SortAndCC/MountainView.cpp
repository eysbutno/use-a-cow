#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 
typedef long long ll;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("mountains.in", "r", stdin);
    freopen("mountains.out", "w", stdout);
    int n; cin >> n;
    vector<pair<ll, ll>> mtns(n);
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        mtns[i].f = x - y, mtns[i].s = x + y;
    }
    sort(begin(mtns), end(mtns), [&](pair<ll, ll> m1, pair<ll, ll> m2) {
        if (m1.f == m2.f) return m1.s > m2.s;
        return m1.f < m2.f;
    });
    ll right = -1, vis = 0;
    for (auto i : mtns) {
        if (i.s > right) {
            vis++, right = i.s;
        }
    }
    cout << vis << '\n';
}
/*
Create a vector of the starting and ending
x locations of each mountains. Sort
by the left location. If two mountains
have the same start, then put the biggest one 
first. Store the rightmost location that
is covered by a previous mountain. If that location
is less than the current mountain's right position,
then the current mountain is visible.
*/