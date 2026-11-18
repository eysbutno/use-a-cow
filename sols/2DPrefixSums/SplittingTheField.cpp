#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
typedef long long ll;

ll solve(vector<pair<ll, ll>>& cows) {
    sort(begin(cows), end(cows), [&](auto x, auto y){
        if (x.f == y.f) return x.s > y.s;
        return x.f < y.f;
    });
    ll n = cows.size();
    vector<ll> up1(n), down1(n), up2(n), down2(n);
    up1[0] = cows[0].s, down1[0] = cows[0].s;
    for (ll i = 1; i < n; i++) {
        up1[i] = max(up1[i - 1], cows[i].s);
        down1[i] = min(down1[i - 1], cows[i].s);
    }
    up2[n - 1] = cows[n - 1].s, down2[n - 1] = cows[n - 1].s;
    for (ll i = n - 2; i >= 0; i--) {
        up2[i] = max(up2[i + 1], cows[i].s);
        down2[i] = min(down2[i + 1], cows[i].s);
    }
    ll best = (cows[n - 1].f - cows[0].f) * 
        (up1[n - 1] - down1[n - 1]);
    
    for (ll i = 0; i < n - 1; i++) {
        ll rect1 = (cows[i].f - cows[0].f) *
            (up1[i] - down1[i]);
        ll rect2 = (cows[n - 1].f - cows[i + 1].f) *
            (up2[i + 1] - down2[i + 1]);
        best = min(best, rect1 + rect2);
    }
    return (cows[n - 1].f - cows[0].f) * 
        (up1[n - 1] - down1[n - 1]) - best;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("split.in", "r", stdin);
    freopen("split.out", "w", stdout);
    ll n; cin >> n;
    vector<pair<ll, ll>> cows(n);
    for (auto& i : cows) {
        cin >> i.f >> i.s;
    }
    ll vert = solve(cows);
    for (ll i = 0; i < n; i++) {
        swap(cows[i].f, cows[i].s);
    }
    ll horiz = solve(cows);
    cout << max(vert, horiz) << '\n';
}
/*
Algorithm:
Use a sweep line to find the maximum and minimum
y values for a certain position. Do it from left
to right and right to left. Get your answer for a vertical 
line. Swap all the coordinates to get the result for a horizontal
line splitting the two enclosures.
*/