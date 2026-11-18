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
    vector<int> a(n), b(n);
    for (int& i : a) {
        cin >> i;
    }
    for (int& i : b) {
        cin >> i;
    }
    ll sum = 0;
    int mn = INT_MAX, mx = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > b[i]) {
            swap(a[i], b[i]);
        }
        sum += b[i] - a[i];
        mx = max(a[i], mx);
        mn = min(b[i], mn);
    }
    if (mn < mx) {
        sum += 2 * (mx - mn);
    }
    cout << sum << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) solve();
}
/**
 * Each pair of numbers can be represented
 * as an "interval". The only case where
 * the total lengths increase is when 
 * a_1 < a_2, and b_1 < b_2, with
 * a_i < b_i.
 * 
 * Thus, the answer is just the sum + 
 * 2 * (max(a_i) - min(b_i)), assuming
 * mx >= mn.
 * 
 * Note: if (a[i] > b[i]), we swap the
 * two so the interval logic makes more sense.
 * Also, if pair i gets swapped, the answer doesn't change.
*/