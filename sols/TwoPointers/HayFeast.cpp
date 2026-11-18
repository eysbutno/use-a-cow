#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("hayfeast.in", "r", stdin);
    freopen("hayfeast.out", "w", stdout);
    ll n, m; cin >> n >> m;
    vector<pll> bales(n);
    for (auto& i : bales) {
        cin >> i.f >> i.s;
    }
    ll sum = 0, res = INT_MAX;
    int l = 0, r = 0;
    multiset<ll> active;
    for (; l < n; l++) {
        while (r < n && sum < m) {
            active.ins(bales[r].s);
            sum += bales[r++].f;
        }
        if (sum < m) continue;
        sum -= bales[l].f;
        ckmin(res, *active.rbegin());
        active.erase(active.find(bales[l].s));
    }
    cout << res << '\n';
}
/**
 * Problem: Haybale Feast
 * Algorithm: Two pointers
 * it. LMAO.
*/