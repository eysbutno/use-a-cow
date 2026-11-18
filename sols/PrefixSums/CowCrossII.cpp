#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);
    int n, k, b; cin >> n >> k >> b;
    vector<int> pf(n + 1);
    while (b--) {
        int idx; cin >> idx;
        pf[idx]++;
    }
    for (int i = 1; i <= n; i++) {
        pf[i] += pf[i - 1];
    }
    int ans = 2e9;
    for (int i = 1; i + k <= n; i++) {
        ans = min(ans, pf[i + k] - pf[i]);
    }
    cout << ans << "\n";
}