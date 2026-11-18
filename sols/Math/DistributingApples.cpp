#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 
 
const int MOD = 1e9 + 7;
const int N = 2e6 + 1;
template<class T> bool smin(T& a, T b) {
    return (b < a ? a = b, 1 : 0);
}
template<class T> bool smax(T& a, T b) {
    return (b > a ? a = b, 1 : 0);
}
ll expo(ll x, ll n, ll m) {
    x %= m;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = res * x % m;
        x = x * x % m;
        n >>= 1;
    }
    return res;
}
ll inv(ll x) {
    return expo(x, MOD - 2, MOD);
}
ll fact[N], invFact[N];
int main() {
    fact[0] = 1, invFact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
    auto binom = [&](ll n, ll k) {
        return (fact[n] * invFact[k] % MOD * 
            invFact[n - k]) % MOD;
    };
    int n, m; cin >> n >> m;
    cout << binom(n + m - 1, n - 1);
}