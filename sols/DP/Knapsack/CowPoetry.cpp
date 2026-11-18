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

const int N = 5001;
const int MOD = 1e9 + 7;
ll dp[N], res[N];
int p[N], pi[N][N];
ll expo(ll x, ll n) {
    x %= MOD;
    ll res = 1;
    while (n > 0) {
        if (n % 2) res = res * x % MOD;
        x = x * x % MOD;
        n >>= 1;
    }
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
    int n, m, k; cin >> n >> m >> k;
    set<int> dist;
    for (int i = 0; i < n; i++) {
        int x, y; cin >> x >> y;
        pi[y][x]++, p[x]++;
        dist.ins(y);
    }
    dp[0] = 1;
    for (int i = 0; i <= k; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] += dp[i - j] * p[j];
            dp[i] %= MOD;
        }
    }
    for (int i : dist) {
        for (int j = 1; j <= k; j++) {
            res[i] += dp[k - j] * pi[i][j];
            res[i] %= MOD;
        }
    }
    vector<int> cnt(26);
    for (int i = 0; i < m; i++) {
        char c; cin >> c;
        cnt[c - 'A']++;
    }
    ll ans = 1;
    for (int i = 0; i < 26; i++) {
        if (!cnt[i]) continue;
        ll tot = 0;
        for (int j : dist) {
            tot += expo(res[j], cnt[i]);
            tot %= MOD;
        }
        ans *= tot, ans %= MOD;
    }
    cout << ans << '\n';
}
/**
 * TASK: Cow Poetry.
 * Calculate s[i] to be the number of
 * ways to end a sentence with a word
 * of rhyme i, using knapsack DP.
 * 
 * To calculate the final result, 
 * you just do a little bit of factoring.
 * Basically, by adding all the possible
 * assignments for each letter, and multiplying
 * these results out, it covers every case.
 * Why? IDK, I read the editorial....
*/