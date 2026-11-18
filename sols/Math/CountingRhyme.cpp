#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    int n; cin >> n;
    vector<int> freq(n + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x, ++freq[x];
    }
    vector<ll> dp(n + 1);
    for (int i = n; i >= 1; i--) {
        int mults = freq[i];
        for (int j = i * 2; j <= n; j += i) {
            mults += freq[j];
            dp[i] -= dp[j];
        }
        dp[i] += (ll) mults * (mults - 1) / 2;
    }
    vector<bool> bad(n + 1);
    for (int i = 1; i <= n; i++) if (freq[i]) {
        for (int j = i; j <= n; j += i) {
            bad[j] = true;
        }
    }
    ll sum = 0;
    for (int i = 1; i <= n; i++) {
        if (!bad[i]) sum += dp[i];
    }
    cout << sum << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: Counting Rhyme (CF)
 * Premise: Find # of pairs such that:
 * a_i, a_j are not divisible by any other
 * number in the array.
 * 
 * Observe that gcd(a_i, a_j) cannot be divisible
 * by any a_k; this simplifies the structure of the problem.
 * First, calculate the # of pairs that form some gcd z. This is
 * initially just pairing up any multiple of gcd z. However, it's
 * possible that these multiples have a GCD of some multiple of z,
 * not z itself, so we need to subtract some stuff.
*/