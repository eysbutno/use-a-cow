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
const int MX = 2e5 + 1;
vector<int> divs[MX];
void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    map<int, bool> seen;
    map<int, int> in, out;
    for (int i : a) seen[i] = true;
    for (int i : a) {
        // calculate in & out arrays
        for (int j : divs[i]) if (j != i) {
            if (seen.count(j)) {
                ++in[i], ++out[j];
            }
        }
    }
    ll res = 0;
    for (int i : a) {
        res += (ll) in[i] * out[i];
    }
    cout << res << "\n";
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    for (int i = 1; i < MX; i++) {
        for (int j = i; j < MX; j += i) {
            divs[j].push_back(i);
        }
    }
    int t = 1; cin >> t;
    while (t--) solve();
}
/**
 * TASK: D. Air Taxi Game (HPI).
 * Observation 1:
 * For some triple, gcd(i, j) = j & lcm(j, k) = j.
 * Proof: gcd(i, j) <= j <= lcm(j, k) => both = j.
 * 
 * Originally, I did multiples stuff. But that 
 * TLEs if there are like 10^4 tests each with a
 * max element of 2 * 10^5. So then just use
 * divisors, cuz N * sqrt(2 * 10^5) doesn't TLE.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Monotonicity? Concavity? Anything else?
  * 4. Prove/justify any observations.
  * 5. If there are 1e9+7 edge cases and it's
  *    impossible to implement, maybe it's not right.
  * 6. For math formulas, try rewriting them.
  * 7. Break down the problem, or maybe reframe it.
  * 8. Loop through common techniques... binary search?
  *    DP? DFS/BFS/Graphs? 
  * 9. If your idea is almost certainly right, try some
  *    optimization techniques. Small to large merging?
  *    Deleting unnecessary stuff? Using a set? IDK.
*/