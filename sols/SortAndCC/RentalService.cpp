#include <bits/stdc++.h>
using namespace std;
#define ll long long

void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
struct Order {
    int a, p;
    bool operator<(const Order &y) {
        return p > y.p;
    }
};
int main() {
    setIO("rental");
    int n, m, r; cin >> n >> m >> r;
    vector<int> cows(n), rent(r); 
    vector<Order> orders(m);
    for (int i = 0; i < n; i++) {
        cin >> cows[i];
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        orders[i] = {a, b};
    }
    for (int i = 0; i < r; i++) {
        cin >> rent[i];
    }
    sort(begin(rent), end(rent), greater<int>());
    sort(begin(cows), end(cows), greater<int>());
    sort(begin(orders), end(orders));
    vector<ll> rpf(n + 1), opf(n + 1);
    for (int i = 0; i < n; i++) {
        rpf[i + 1] = rpf[i];
        if (i < r) rpf[i + 1] += rent[i];
    }
    int idx = 0;
    for (int i = 0; i < n; i++) {
        ll sold = 0; int amt = cows[i];
        while (amt > 0 && idx < m) {
            int soldAmt = min(amt, orders[idx].a);
            sold += orders[idx].p * soldAmt;
            amt -= soldAmt;
            if (orders[idx].a > soldAmt) {
                orders[idx].a -= soldAmt;
                break;
            } else {
                idx++;
            }
        }
        opf[i + 1] = opf[i] + sold;
    }
    ll best = -1;
    for (int i = 0; i <= n; i++) {
        best = max(best, rpf[i] + opf[n - i]);
    }
    cout << best << "\n";
}
/*
Sorting, Prefix Sums
Algorithm:
Create prefix sums for dedicating a certain amount of cows
to either renting or selling; Then find the optimal solution
*/