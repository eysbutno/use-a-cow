#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
void solve() {
    int n; cin >> n;
    vector<pair<int, int>> dept(n);
    multiset<int> g;
    for (auto& i : dept) {
        cin >> i.f >> i.s;
        g.insert(i.f);
    }
    sort(begin(dept), end(dept),
        [&](auto& x, auto& y) {
        if (x.s == y.s) return x.f < y.f;
        return x.s > y.s;
    });
    int res = INT_MAX, most = INT_MIN;
    for (int i = 1; i < n; i++) {
        res = min(res, abs(dept[i].f - dept[0].s));
    }
    for (int i = 0; i < n; i++) {
        // b_i most expensive for f2
        g.erase(g.find(dept[i].f));
        if (i == 0) {
            most = dept[i].f;
            continue;
        }
        auto it = g.lower_bound(dept[i].s);
        if (it != end(g) && *it >= most) {
            res = min(res, abs(dept[i].s - *it));
        }
        if (it != begin(g) && *prev(it) >= most) {
            res = min(res, abs(dept[i].s - *prev(it)));
        }
        res = min(res, abs(dept[i].s - most));
        most = max(most, dept[i].f);
    }
    cout << res << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
}