#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = array<int, 2>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
namespace Math {
    vector<vector<int>> pfactors;
    vector<int> primes;
    void init(int bound, int pos) {
        for (int i = 2; i <= bound; i++) {
            bool ok = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) ok = false;
            }
            if (ok) primes.push_back(i);
        }
        pfactors.resize(pos);
        for (int i = 2; i < pos; i++) {
            for (int j : primes) {
                if (i % j == 0) {
                    pfactors[i].push_back(j);
                }
            }
        }
    }
};
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    const int POS = 1e4 + 1;
    Math::init(100, POS);
    vector dp(n, vector(POS, 0));
    vector<map<int, int>> factors(n);
    auto dfs = [&](int u, int p, auto&& dfs) -> void {
        for (int i = 2; i < POS; i++) {
            if (i != a[u]) dp[u][i] = i;
            if (Math::pfactors[i].empty()) {
                dp[u][i] = numeric_limits<int>::max();
            }
        }
        for (int v : adj[u]) {
            if (v == p) continue;
            dfs(v, u, dfs);
            for (int i = 2; i < POS; i++) {
                if (Math::pfactors[i].empty()) continue;
                int best = numeric_limits<int>::max();
                for (int j : Math::pfactors[i]) {
                    smin(best, factors[v][j]);
                }
                dp[u][i] += best;
            }
        }
        for (int i : Math::primes) {
            int best = numeric_limits<int>::max();
            for (int j = i; j < POS; j += i) {
                smin(best, dp[u][j]);
            }
            factors[u][i] = best;
        }
    };
    dfs(0, -1, dfs);
    int res = numeric_limits<int>::max();
    for (int i = 2; i < POS; i++) {
        smin(res, dp[0][i]);
    }
    cout << res << "\n";
}
/**
 * Let dp[i][j] be cost to make the subtree of i
 * harmonious, if node i has a value of j. 
 * 1. Each child of i must be divisible by a prime factor of j.
 * 2. The highest j can be is 2 * (# of nodes), because otherwise
 *    replacing everything is cheaper.
 * With this info, you can do some math and DP to calculate dp[i][j].
*/