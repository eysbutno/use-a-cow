#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main() {
    int n; cin >> n;
    vector<ll> s(n); s[0] = 1;
    ll pf = 0, ans = 0;
    for (int i = 0; i < n; i++) {
        ll a; cin >> a; pf += a;
        s[(pf % n + n) % n]++;
    }
    for (ll i : s) {
        ans += i * (i - 1) / 2;
    }
    cout << ans << "\n";
}
/*
Type: Prefix Sums
Time Complexity: O(N)
Algorithm:
Sum of subarray (i, j)
is pf[j] - pf[i - 1]
if subarray(i, j) % n = 0,
then pf[j] = pf[i - 1].
In order to figure out all possible pairings
of these equal prefixes, we use...
COMBINATORICS!
Combination of i subarrays, choose 2
is (i!)/(2!(i-2)!), or
i * (i - 1) / 2
*/