#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m, k; 
    cin >> n >> m >> k;
    vector<pll> cws(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        cws[i] = {x, y};
    }
    sort(all(cws));
    reverse(all(cws));
    ll cnt = m;
    ll used = 0;
    map<ll, ll> teams;
    for (int i = 0; i < n; i++) {
        if (cnt == 0) break;
        ll num = min(cnt, cws[i].s);
        cnt -= num; 
        teams[cws[i].f] += num;
        cws[i].s -= num;
        used += num;
    }
    for (int i = 0; i < n; i++) {
        if (!cws[i].s) continue;
        auto it = teams.lower_bound(cws[i].f + k);
        while (it != end(teams) && cws[i].s) {
            pll a = *it;
            ll num = min(a.s, cws[i].s);
            teams[a.f] -= num;
            teams[cws[i].f] += num;
            cws[i].s -= num;
            if (!teams[a.f]) {
                teams.erase(a.f);
                it = teams.lower_bound(a.f);
            } else {
                ++it;
            }
            used += num;
        }
    }
    cout << used << '\n';
}