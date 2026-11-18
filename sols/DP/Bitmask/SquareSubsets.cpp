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
 
template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
const int MOD = 1e9 + 7;
ll dp[2][1 << 19], f[2][71];
int mask[71], p[19];
bool isPrime(int x) {
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}
void build() {
    int idx = 0;
    for (int i = 2; i <= 70; i++) {
        if (isPrime(i)) p[idx++] = i;
    }
    for (int i = 1; i <= 70; i++) {
        int msk = 0, cur = i;
        for (int j = 0; j < 19; j++) {
            while (cur % p[j] == 0) {
                msk ^= (1 << j);
                cur /= p[j];
            }
        }
        mask[i] = msk;
        f[0][i] = 1;
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    build();
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        int p1 = f[0][x], p2 = f[1][x];
        f[0][x] += p2, f[0][x] %= MOD;
        f[1][x] += p1, f[1][x] %= MOD;
    }
    dp[0][0] = 1;
    for (int i = 1; i <= 70; i++) {
        for (int j = 0; j < (1 << 19); j++) {
            dp[1][j] += (dp[0][j] * f[0][i]) % MOD;
            dp[1][j] += (dp[0][j ^ mask[i]] * f[1][i]) % MOD;
            dp[1][j] %= MOD;
        }
        for (int j = 0; j < (1 << 19); j++) {
            swap(dp[1][j], dp[0][j]);
            dp[1][j] = 0;
        }
    }
    cout << dp[0][0] - 1 << '\n';
}
/**
 * TASK: Square Subsets.
 * OK, there are 19 prime divisors under 70...
 * very convenient!
 * 
 * So, I'm thinking that we can prime factorize
 * each number. If the power is even, then we 
 * mark it as a 0 in the bitmask. Otherwise, 
 * mark it as a 1 in the bitmask.
 * 
 * Let dp[i][j] be the # of ways to choose some elements
 * which are <= i, from a, and their product results
 * in a bitmask j. Then, we can perform the following
 * transition:
 * 
 * dp[i][j] = dp[i - 1][j] * # of ways to choose an
 * even # of number i.
 * dp[i][j] = dp[i - 1][j ^ mask[i]] * # of ways to choose
 * odd # of number i.
 * 
 * NOTE: You must drop a dimension from the DP array. Since
 * the result only depends on the previous result, we can
 * successfully reduce it to 2 dimensions.
*/