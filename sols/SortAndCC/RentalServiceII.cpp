#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
typedef long long ll;

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);
    int n, m, r; cin >> n >> m >> r;
    vector<int> cows(n), rent(r);
    vector<pair<int, int>> orders(m);
    for (int& i : cows) cin >> i;
    for (auto& i : orders) cin >> i.s >> i.f;
    for (int& i : rent) cin >> i;
    sort(begin(rent), end(rent), greater<int>());
    sort(begin(cows), end(cows), greater<int>());
    sort(begin(orders), end(orders));
    vector<ll> sell(n + 1), lease(n + 1);
    for (int i = 0; i < n; i++) {
        lease[i + 1] = lease[i];
        if (i < r) lease[i + 1] += rent[i];
    }
    int orderIdx = m - 1;
    for (int i = 0; i < n; i++) { // using cow i
        while (orderIdx >= 0 && cows[i]) {
            ll amt = min(orders[orderIdx].s, cows[i]);
            sell[i + 1] += orders[orderIdx].f * amt;
            cows[i] -= amt, orders[orderIdx].s -= amt;
            if (!orders[orderIdx].s) orderIdx--;
        }
        sell[i + 1] += sell[i];
    }
    ll ans = -1;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, sell[i] + lease[n - i]);
    }
    cout << ans << '\n';
}