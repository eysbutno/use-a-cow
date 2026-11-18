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
    vector<int> p(n), c(n);
    for (int &i : p) cin >> i, --i;
    for (int &i : c) cin >> i, --i;
    vector<bool> seen(n);
    int res = MX; // functionally infinite
    auto process = [&](int u) -> void {
        vector<int> cycle;
        while (!seen[u]) {
            cycle.push_back(u);
            seen[u] = true;
            u = p[u];
        }
        int z = sz(cycle);
        for (int i : divs[z]) {
            // try out each divisor value.
            vector<bool> proc(z);
            for (int j = 0; j < z; j++) {
                if (!proc[j]) {
                    // process this current cycle.
                    vector<int> cur;
                    int ptr = j;
                    do {
                        cur.push_back(cycle[ptr]);
                        proc[ptr] = true;
                        ptr = (ptr + i) % z;
                    } while (ptr != j);
                    bool bad = false;
                    for (int i = 1; i < sz(cur); i++) {
                        if (c[cur[i - 1]] != c[cur[i]]) {
                            bad = true; break;
                        }
                    }
                    if (!bad) {
                        smin(res, i);
                        break;
                    }
                }
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (!seen[i]) process(i);
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
 * TASK: D. Infinite Path (CF)
 * Graph is a functional graph, so the infinite
 * path is just a cycle.
 * 
 * The remapping operation basically shifts over the
 * cycle. In formal terms, if we have a cycle v_i,
 * then p^k[v_i] = v_((i + k) % size). For each value
 * of k, there will be gcd(cycle_len, k) subcycles. 
 * Because of that, each cycle will be m/gcd(cycle_len, k)
 * long. Obviously, we mainly care about the cases where
 * gcd(cycle_len, k) is NOT 1. So, iterate over all divisors
 * of cycle_len.
*/
/**
  * 1. Can a graph be constructed?
  * 2. How can we reuse information?
  * 3. Prove/justify any observations.
  * 4. For math formulas, try rewriting them.
  * 5. Break down the problem, or maybe reframe it.
  * 6. Try multiple techniques.
*/