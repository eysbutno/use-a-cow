#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("measurement.in", "r", stdin);
    freopen("measurement.out", "w", stdout);
    int n, g; cin >> n >> g;
    vector<pair<pair<int, int>, int>> days(n);
    for (int i = 0; i < n; i++) {
        int d, id, m; cin >> d >> id >> m;
        days[i] = {{d, id}, m};
    }
    sort(begin(days), end(days));
    map<int, ll> prod;
    multiset<ll> amts;
    for (int i = 0; i < n; i++) amts.insert(0);
    ll maxMilk = 0, cnt = n;
    int ans = 0;
    for (auto i : days) {
        int id = i.f.s, dif = i.s, old = prod[id];
        amts.erase(amts.find(old)), amts.insert(old + dif);
        prod[id] = old + dif;
        if (prod[id] > maxMilk) {
            ans += (cnt > 1 || old != maxMilk);
            maxMilk = prod[id], cnt = 1;
        } else if (prod[id] == maxMilk) {
            ans++, cnt++;
        } else if (old == maxMilk) {
            auto it = amts.rbegin();
            ll prevMax = maxMilk, prevCnt = cnt;
            maxMilk = *it, cnt = amts.count(*it);
            ans += (cnt > 1 || prevCnt > 1 || maxMilk != prod[id]);
        }
    }
    cout << ans << '\n';
}
/*
Sort all the entries by date.
Keep each cow's production value stored in a map,
and keep the amounts each cow produces stored in a set.
You don't need to worry about which cow produces how much,
just the top few cows.
*/