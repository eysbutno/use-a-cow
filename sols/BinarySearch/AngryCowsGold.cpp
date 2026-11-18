#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);
    int n; cin >> n;
    vector<ll> locs(n);
    for (int i = 0; i < n; i++) {
        cin >> locs[i]; locs[i] *= 2;
    }
    sort(begin(locs), end(locs));
    auto worksRight = [&](ll start, ll radius) {
        ll prev = start, idx = 0;
        while (prev < locs[n - 1]) {
            while (idx + 1 < n && 
                locs[idx + 1] <=
                prev + radius) {
                ++idx;
            }
            if (prev == locs[idx]) {
                return false;
            }
            prev = locs[idx];
            radius -= 2;
        }
        return true;
    };
    auto worksLeft = [&](ll start, ll radius) {
        ll prev = start, idx = n - 1;
        while (prev > locs[0]) {
            while (idx - 1 >= 0 && 
                locs[idx - 1] >= 
                prev - radius) {
                --idx;
            }
            if (prev == locs[idx]) {
                return false;
            }
            prev = locs[idx];
            radius -= 2;
        }
        return true;
    };
    auto check = [&](ll rad) {
        ll low = locs[0], high = locs[n - 1];
        while (low < high) {
            ll mid = (low + high) / 2;
            if (worksRight(mid, rad)) high = mid;
            else low = mid + 1;
        }
        return worksLeft(low, rad);
    };
    ll low = 0, high = 2e9;
    while (low < high) {
        ll mid = (low + high) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low / 2 << '.' << ((low % 2) ? 5 : 0);
}
/*
Binary search the blast radius.
To check if a blast radius is valid,
we binary search the lowest location
where you can blast all the haybales
to the right. After that, check if you
can detonate all the haybales to the left
at this position. If you can, it's a valid
radius amount.

Note: the locations and radiuses are multiplied
by two to avoid floating point numbers.
*/