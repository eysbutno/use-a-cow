#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

struct Order {
    ll a, b, c;
};
void solve() {
    ll n, tc, tm; 
    cin >> n >> tc >> tm;
    vector<Order> ord(n);
    for (int i = 0; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        ord[i] = {a, b, c};
    }
    auto check = [&](ll m) {
        ll d = tc + tm - m;
        ll lb = max((ll) 1, d - tm), 
            ub = min(tc, d - 1);
        for (int i = 0; i < n; i++) {
            ll a = ord[i].a, 
                b = ord[i].b,
                c = ord[i].c;
            if (a > b) {
                ub = min(ub, (c - 
                    b * d) / (a - b));
            } else if (a < b) {
                lb = max(lb, (b * d - c + 
                    (b - a - 1)) / (b - a));
            } else {
                if (a * d > c) {
                    return false;
                }
            }
        }
        return lb <= ub;
    };
    ll low = 0, high = tc + tm;
    while (low < high) {
        int mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int t; cin >> t;
    while (t--) solve();
    return 0;
}
/*
Binary search the # of moonies 
Bessie will need.

To determine whether an amount of 
moonies is adequate, we need
to set up an upper and lower bound.

Take a value x (time / cookie) and
a value y (time / muffin). We
can derive two inequalities with this:
1: x + y = tc + tm - mid
2: ax + by <= c

Substitute y into #2 to get our 
upper bound inequality. To
get our lower bound inequality,
substitute x into #2 and then
substitute y in the following
inequality. Run through
each order, maintaining
these upper and lower
bounds. If there is a
valid interval where Bessie
satisfies all the orders,
then that amt of moonies
is valid.
*/