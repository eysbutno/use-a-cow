#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);
    ll n, m; cin >> n >> m;
    vector<pair<ll, ll>> grass(m);
    for (auto& i : grass) {
        cin >> i.f >> i.s;
    }
    sort(begin(grass), end(grass));
    auto check = [&](ll mid) {
        ll cows = 0;
        ll prev = -2e18;
        for (auto i : grass) {
            ll start = max(i.f, prev + mid);
            if (start <= i.s) {
                ll dist = i.s - start + 1;
                ll num = (dist + mid - 1) / mid;
                if (num != 0) {
                    cows += num;
                    prev = start + (num - 1) * mid;
                }
            }
            if (cows >= n) return true;
        }
        return false;
    };
    ll low = 0, high = grass[m - 1].s;
    while (low < high) {
        ll mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
/*
Binary search the distance between the cows.
For the check() function, go through each patch 
and place all the cows that you can.
If the cows placed is >= n, return true, otherwise return false
*/