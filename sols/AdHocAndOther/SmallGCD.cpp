#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5;
vector<ll> dv[N + 1];
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int& i : a) {
        cin >> i;
    }
    sort(begin(a), end(a));
    vector<ll> nums(N + 1),
        cnt(N + 1);
    for (int i = 0; i < n; i++) {
        for (int d : dv[a[i]]) {
            cnt[d] += (n - i - 1) * nums[d];
            nums[d]++;
        }
    }
    ll res = 0;
    for (int i = N; i >= 1; i--) {
        for (int j = i * 2; j <= N; j += i) {
            cnt[i] -= cnt[j];
        }
        res += cnt[i] * i;
    }
    cout << res << '\n';
}
int main() {
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            dv[j].pb(i);
        }
    }
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}
/**
 * Precompute divisors. Do some
 * wacky math.
*/