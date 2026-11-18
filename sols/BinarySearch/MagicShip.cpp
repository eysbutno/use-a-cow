#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

int main() {
    ll x1, y1; cin >> x1 >> y1;
    ll x2, y2; cin >> x2 >> y2;
    int n; cin >> n;
    vector<pair<ll, ll>> pf(n + 1);
    for (int i = 1; i <= n; i++) {
        char dir; cin >> dir;
        if (dir == 'U') pf[i].s++;
        else if (dir == 'D') pf[i].s--;
        else if (dir == 'L') pf[i].f--;
        else pf[i].f++;
        pf[i].f += pf[i - 1].f;
        pf[i].s += pf[i - 1].s;
    }
    auto check = [&](ll mid) {
        ll dx = x2 - (pf[n].f * 
            (mid / n) + pf[mid % n].f),
            dy = y2 - (pf[n].s * 
            (mid / n) + pf[mid % n].s);
        ll days = abs(dx - x1) + abs(dy - y1);
        return days <= mid;
    };
    ll low = 0, high = 1e18;
    bool found = false;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) {
            high = mid;
            found = 1;
        } else {
            low = mid + 1;
        }
    }
    if (found) cout << low << '\n';
    else cout << -1 << '\n';
}
/*
Binary search the # of ideas.
F(days) <- true or false is monotonic
for obvious reasons. Use prefix sums
to do the calculations fast.
*/