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

const int ZERO = 2000;
const int MOD = 1e9 + 7;
ll dp[4001][4001], fact[8001], invFact[8001];
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
ll binom(int n, int k) {
    return (fact[n] * invFact[k] % MOD * 
            invFact[n - k]) % MOD;
}
void precalc() {
    fact[0] = 1, invFact[0] = 1;
    for (int i = 1; i <= ZERO * 4; i++) {
        fact[i] = (fact[i - 1] * i) % MOD;
        invFact[i] = inv(fact[i]);
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    precalc(); // binom coeff
    vector<pii> sk(n);
    for (int i = 0; i < n; i++) {
        int a, b; cin >> a >> b;
        dp[ZERO - a][ZERO - b]++;
        sk[i] = {a, b};
    }
    for (int i = 0; i <= ZERO * 2; i++) {
        for (int j = 0; j <= ZERO * 2; j++) {
            if (i > 0) dp[i][j] += dp[i - 1][j];
            if (j > 0) dp[i][j] += dp[i][j - 1];
            dp[i][j] %= MOD;
        }
    }
    ll res = 0;
    for (int i = 0; i < n; i++) {
        auto [a, b] = sk[i];
        res += dp[ZERO + a][ZERO + b];
        res -= binom(a * 2 + b * 2, a * 2);
        res = (res % MOD + MOD) % MOD;
    }
    res = (res * inv(2)) % MOD;
    cout << (res + MOD) % MOD << '\n';
}
/**
 * TASK: BBQ Hard (AtCoder).
 * Note how N is big, but A_i and B_i are
 * comparatively smaller.
 * 
 * Observation 1: 
 * Say we have two skewers <a_i, b_i>, and <a_j, b_j>.
 * The # of skewers you can make is the # of paths from
 * <-a_i, -b_i> to <a_j, b_j>.
 * 
 * Observation 2:
 * The answer for each skewer (if this skewer is used
 * in the combination) is the sum of paths to this skewer.
 * 
 * So, we can initially take the answer as the sum of 
 * all paths from any skewer to any other skewer. Then,
 * we need to subtract one self path (b/c a skewer cannot
 * pair up with itself), and divide by two (because right
 * now we are double counting).
 * 
 * Note that you multiply by the modular inverse of 2.
*/