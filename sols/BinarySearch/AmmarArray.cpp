#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using pdi = pair<double, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n), c(n);
    for (int& i : a) cin >> i;
    map<int, vector<ll>> col;
    for (int i = 0; i < n; i++) {
        int c; cin >> c;
        col[c].push_back(a[i]);
    }
    for (auto& i : col) {
        ll running = 0;
        for (int j = 0; j < size(i.s); j++) {
            running += col[i.f][j];
            col[i.f][j] = running;
        }
    }
    map<int, ll> dx;
    ll tot = 0;
    int q; cin >> q;
    auto calc = [&](int c, int idx) {
        ll net = tot - dx[c];
        ll res = net * (idx + 1) +
            col[c][idx];
        return res;
    };
    auto biSearch = [&](int c, ll mx) {
        int low = 0, high = size(col[c]) - 1;
        while (low < high) {
            int mid = (low + high + 1) / 2;
            ll sum = calc(c, mid); 
            if (sum <= mx) low = mid;
            else high = mid - 1;
        }
        if (calc(c, 0) > mx) {
            return -1;
        }
        return low;
    };
    while (q--) {
        ll t, a, b; 
        cin >> t >> a >> b;
        if (t == 1) {
            tot += b;
            dx[a] += b;
        } else {
            cout << biSearch(a, b) + 1
                << '\n';
        }
    }
    auto test = [&]() {
        cout << "Total:" << '\n';
        cout << tot << '\n';
        cout << "Delta X Map:" << '\n';
        for (auto& i : dx) {
            cout << i.f << ' ' << i.s << '\n';
        }
        cout << '\n';
        cout << "Prefix Sum:" << '\n';
        for (auto& i : col) {
            cout << i.f << ": ";
            for (int j : i.s) cout << j << ' ';
            cout << '\n';
        }
        cout << "Calc Method Testing:" << '\n';
        cout << calc(2, 2) << '\n';
    };
    // test();
}
/*
Maintain total increment
and delta x array. Binary
search longest prefix.
Note: can make implementation
shorter. Too lazy to though.
*/