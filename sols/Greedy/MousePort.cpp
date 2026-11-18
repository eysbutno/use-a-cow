#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    ll a, b, c; cin >> a >> b >> c;
    vector<ll> usb, ps2;
    ll n; cin >> n;
    while (n--) {
        ll p; string t; cin >> p >> t;
        if (t == "USB") usb.push_back(p);
        else ps2.push_back(p);
    }
    sort(begin(usb), end(usb));
    sort(begin(ps2), end(ps2));
    ll idx1 = 0, cost = 0, bought = 0;
    while (a > 0 && idx1 < usb.size()) {
        cost += usb[idx1], idx1++, bought++, a--;
    }
    ll idx2 = 0;
    while (b > 0 && idx2 < ps2.size()) {
        cost += ps2[idx2], idx2++, bought++, b--;
    }
    while ((idx1 < usb.size() || idx2 < ps2.size()) && c > 0) {
        if (idx1 < usb.size() && idx2 < ps2.size()) {
            if (usb[idx1] < ps2[idx2]) {
                cost += usb[idx1], idx1++;
            } else {
                cost += ps2[idx2], idx2++;
            }
        } else if (idx1 < usb.size()) {
            cost += usb[idx1], idx1++;
        } else {
            cost += ps2[idx2], idx2++;
        }
        c--, bought++;
    }
    cout << bought << " " << cost;
}