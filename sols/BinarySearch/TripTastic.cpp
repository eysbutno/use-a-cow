#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> pf(n + 1, vector<ll>(m + 1));
    vector<pair<int, int>> locs;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> pf[i][j];
            if (pf[i][j]) locs.push_back({i, j});
            pf[i][j] += pf[i - 1][j] + pf[i][j - 1]
                 - pf[i - 1][j - 1];
        }
    }
    auto check = [&](int mid) {
        for (auto i : locs) {
            int r = i.first, c = i.second;
            ll sum = pf[min(n, r + mid)][min(m, c + mid)]
                - pf[max(0, r - mid - 1)][min(m, c + mid)]
                - pf[min(n, r + mid)][max(0, c - mid - 1)]
                + pf[max(0, r - mid - 1)][max(0, c - mid - 1)];
            if (sum > k) return true;
        }
        return false;
    };
    int low = 0, high = max(n, m);
    bool valid = false;
    while (low < high) {
        int mid = (low + high) / 2;
        if (check(mid)) high = mid, valid = 1;
        else low = mid + 1;
    }
    if (valid) cout << low << '\n';
    else cout << -1 << '\n';
}
int main() {
    int t; cin >> t;
    while (t--) solve();
    return 0;
}