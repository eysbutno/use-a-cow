#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmax(a, b) a = max(a, b)
#define ckmin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

int main() {
    int n, k; 
    cin >> n >> k;
    vector<ll> a(n);
    for (ll& i : a) {
        cin >> i;
    }
    sort(begin(a), end(a));
    auto check = [&](ll mid) {
        ll ops = 0;
        for (int i = n / 2; i < n; i++) {
            ops += max((ll) 0, mid - a[i]);
        }
        return ops <= k;
    };
    ll low = 0, high = 2e9;
    while (low < high) {
        ll mid = low + (high - low + 1) / 2;
        if (check(mid)) low = mid;
        else high = mid - 1;
    }
    cout << low << '\n';
}
/**
 * Binary search a value
 * where we can make (n + 1) / 2
 * numbers >= that value.
*/