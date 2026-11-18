#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

void solve() {
    int n; cin >> n;
    vector<int> p(n);
    for (int& i : p) {
        cin >> i;
    }
    auto check = [&](int mid) {
        int sz = (n % 2) + mid * 2;
        int edge = (n - sz) / 2;
        // how many #s on each side
        int l = 1 + edge, h = n - edge;
        for (int i = 0; i < n; i++) {
            if (p[i] == l) ++l;
            if (l > h) return true;
        }
        return false;
    };
    int low = 0, high = n / 2;
    while (low < high) {
        int mid = (low + high + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    int res = (n % 2) + low * 2;
    cout << (n - res) / 2 << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Observation 1: 
 * Unless the array is already
 * sorted, the pair 1 & n need to have an operation done.
 * The other elements of the array do not matter.
 * 
 * Observation 2:
 * Observation 1 is always repeated until the subarray is sorted or
 * is empty.
 * 
 * Task: How to find the implicit subarray and tell
 * if it's sorted?
 * Answer: Binary search the length
*/