#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 
#define ll long long

ll fib[100005];
const ll MOD = 998244353;
void solve() {
    int n, q; cin >> n >> q;
    vector<ll> a(n + 3);
    while (q--) {
        int l, r; cin >> l >> r;
        a[r + 1] -= fib[r - l + 2] - MOD;
        a[r + 2] -= fib[r - l + 1] - MOD;
        a[l] = (a[l] + 1) % MOD;
        a[r + 1] %= MOD;
        a[r + 2] %= MOD;
    }
    if (n >= 2) {
        a[2] += a[1];
        a[2] %= MOD;
    }
    for (int i = 3; i <= n; i++) {
        a[i] += a[i - 1] + a[i - 2];
        a[i] %= MOD;
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}   
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    fib[0] = 0, fib[1] = 1;
    for (int i = 2; i < 100005; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        fib[i] %= MOD;
    }
    int t; cin >> t;
    while (t--) solve();
}
/*
It's like prefix sums, 
and similar to Pareidolia
in the idea of using a sum
to keep track of all the 
current states of a query.
Too lazy to explain impl.
*/