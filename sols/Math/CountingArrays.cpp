#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smax(T &a, T b) {
    return a < b ? a = b, 1 : 0;
}
template<class T> bool smin(T &a, T b) {
    return a > b ? a = b, 1 : 0;
}
const int MOD = 998244353;
ll expo(ll x, ll n, ll m = MOD) {
    ll res = 1; x %= m;
    for (; n; n >>= 1, x = (x * x) % m) {
        if (n & 1) res = (res * x) % m;
    }
    return res;
}
void solve() {
    int n; ll m;
    cin >> n >> m;
    ll res = 0;
    for (int i = 1; i <= n; i++) {
        res = (res + expo(m, i)) % MOD;
    }
    auto isPrime = [&](int x) -> bool {
        for (int i = 2; i * i <= x; i++) {
            if (x % i == 0) return false;
        }
        return true;
    };
    ll cur = 1, sub = 1;
    for (int i = 1; i <= n; i++) {
        if (cur > m) break;
        if (isPrime(i)) cur *= i;
        sub = (sub * ((m / cur) % MOD)) % MOD;
        res = ((res - sub) % MOD + MOD) % MOD;
    }
    cout << res << "\n";
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * D. Counting Arrays (Codeforces)
 * Obviously, any array CAN have a valid removal
 * sequence (1, 1, 1, 1,....). Maybe complementary count?
 * 
 * OK, so, if an array is unambiguous, then it means that every
 * element MUST be deleted at indice 1. In other words, gcd(a_i, i) != 1,
 * if i > 1 and i <= the current position. For this to be the case, i MUST
 * be divisible by every prime in that range. Thus, yielding our answer.
*/