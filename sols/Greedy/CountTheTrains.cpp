#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> a(n);
    set<int> active;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (active.empty() || a[i] < 
            a[*active.rbegin()]) {
            active.insert(i);
        }
    }
    // active has all the starting
    // indexes for each train
    auto del = [&](int idx) {
        // deletes all greater
        // trains starting from idx
        auto it = active.upper_bound(idx);
        while (it != end(active)) {
            int ptr = *it;
            if (a[ptr] >= a[idx]) {
                active.erase(it);
                it = active.upper_bound(ptr);
            } else {
                break;
            }
        }
    };
    for (int i = 0; i < m; i++) {
        int k, d; 
        cin >> k >> d;
        a[--k] -= d;
        auto it = active.lower_bound(k);
        if (*it != k || it == end(active)) {
            int idx = *prev(it);
            // the train it's a part of
            if (a[idx] > a[k]) {
                active.insert(k);
                del(k);
            }
        } else {
            del(k);
        }
        // del(k) removes all trains with
        // higher speeds than train k
        cout << size(active) << ' ';
    }
    cout << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int t; cin >> t;
    while (t--) solve();
}