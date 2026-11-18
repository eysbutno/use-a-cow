#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("exercise.in", "r", stdin);
    freopen("exercise.out", "w", stdout);
    int n, MOD; cin >> n >> MOD;
    vector<bool> composite(n + 1);
    vector<int> primes;
    for (int i = 2; i <= n; i++) {
        if (composite[i]) continue;
        for (int j = i * i; j <= n; j += i) {
            composite[j] = true;
        }
        primes.push_back(i);
    }
    int sz = size(primes);
    vector<ll> dp(n + 1, 1);
    for (int i = 1; i <= sz; i++) {
        for (int j = n; j >= 0; j--) {
            ll expo = primes[i - 1];
            while (expo <= j) {
                dp[j] += (dp[j - expo] * expo);
                dp[j] %= MOD, expo *= primes[i - 1];
            }
        }
    }
    cout << dp[n] << '\n';
}
/**
 * TASK: Exercise.
 * Observation 1: For a given permutation,
 * you essentially construct a functional graph
 * to see how many iterations it takes to
 * return to its original state.
 * 
 * Observation 2: For that permutation,
 * the answer is the LCM of all the cycle
 * lengths.
 * 
 * Observation 3: It is always possible to create
 * whatever cycle lengths you want, so the problem
 * boils down to the following:
 * Given a number k, is it possible to split up the
 * array into cycles of size a_i, so that lcm(all(a_i))
 * is equal to k?
 * 
 * Observation 4: To construct our cycles, just figure
 * out every group of numbers so that every pair of
 * numbers is pairwise coprime.
 * In other words, sum of prime factors ^ exponent that
 * you use must <= N, so you just find the result.
 * 
 * Algorithm: You only need to consider:
 * A. The primes you've used so far.
 * B. The cows you've used so far.
 * So, initially dp[A][B] = dp[A - 1][B]. Then, when
 * performing the transition, you exponentiate stuff.
*/