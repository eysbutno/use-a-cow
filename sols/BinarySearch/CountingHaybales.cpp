#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0);
    freopen("haybales.in", "r", stdin);
    freopen("haybales.out", "w", stdout);
    int n, q; cin >> n >> q;
    vector<int> bales(n);
    for (int &i : bales) cin >> i;
    sort(begin(bales), end(bales));
    while (q--) {
        int a, b; cin >> a >> b;
        cout << upper_bound(begin(bales), end(bales), b)
            - lower_bound(begin(bales), end(bales), a) << "\n";
    }
}