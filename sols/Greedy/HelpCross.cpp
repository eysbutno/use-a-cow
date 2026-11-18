#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    freopen("helpcross.in", "r", stdin);
    freopen("helpcross.out", "w", stdout);
    int c, n; cin >> c >> n;
    multiset<int> ch;
    vector<pair<int, int>> co(n);
    for (int i = 0; i < c; i++) {
        int t; cin >> t;
        ch.insert(t);
    }
    for (int i = 0; i < n; i++) {
        cin >> co[i].second
        >> co[i].first;
    }
    sort(begin(co), end(co));
    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto chicken = ch.lower_bound(co[i].second);
        if (chicken != end(ch) &&
            *chicken <= co[i].first) {
            ans++; ch.erase(chicken);
        }
    }
    cout << ans << "\n";
}
/*
Type: Sorting, Greedy
Algorithm: Sort by the time that the cow has to leave.
This is an application of the classic scheduling problem.
Next, use std::lower_bound to binary search the best chicken.
NOTE: It's probably okay to use O(N^2) logic,
but it's more likely to TLE
*/