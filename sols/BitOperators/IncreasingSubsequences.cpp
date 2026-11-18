#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    ll x; cin >> x;
    vector<int> a;
    int log2 = 63 - __builtin_clzll(x);
    for (int i = 0; i < log2; i++) {
        a.push_back(i);
    }
    ll targ = x - (1LL << log2);
    for (int i = log2 - 1; i >= 0; i--) {
        if ((targ >> i) & 1) {
            a.push_back(i);
        }
    }
    cout << size(a) << '\n';
    for (int i : a) {
        cout << i << ' ';
    }
    cout << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Observation 1:
 * If you start off by having N increasing
 * elements, there are 2^N increasing subsequences.
 * 
 * Observation 2:
 * If you add some extra numbers in descending order,
 * you can carefully control the final answer.
*/