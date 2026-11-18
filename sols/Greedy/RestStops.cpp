#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
typedef long long ll;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("reststops.in", "r", stdin);
    freopen("reststops.out", "w", stdout);
    int l, n, f, b; cin >> l >> n >> f >> b;
    vector<pair<int, int>> stops(n);
    for (auto &[a, b] : stops) {
        cin >> a >> b;
    }
    sort(begin(stops), end(stops), greater<>());
    ll ans = 0, dist = 0;
    for (const auto& i : stops) {
        if (dist < i.s) {
            ans += (i.s - dist) * 
                (f - b) * i.f;
            dist = i.s;
        }
    }
    cout << ans << '\n';
}