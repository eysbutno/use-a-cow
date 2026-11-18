#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll n, k, m;
bool check(ll mid) {
    ll g = 0, days = k;
    while (g < n && days > 0) {
        ll y = (n - g) / mid;
        if (y <= m) {
            g += days * m;
            break;
        }
        ll lb = y * mid;
        ll time = ((n - g - lb) / y) + 1;
        g += y * time;
        days -= time;
    }
    return g >= n;
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("loan.in", "r", stdin);
    freopen("loan.out", "w", stdout);
    cin >> n >> k >> m;
    ll low = 0, high = n;
    while (low < high) {
        ll mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
/*
Type: Binary Search
Algorithm:
Binary searching y. Simulating each value of y. 

The math:
In order for y to change, it has to move from one interval
to another. In this case, an interval is defined to be
the lower and upper bounds of n - g for our y. We do
some simple math to calculate how many days we need
to go to our next interval, and repeat until y <= m.
*/