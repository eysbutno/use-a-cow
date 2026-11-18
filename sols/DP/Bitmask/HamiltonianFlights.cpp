#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int MOD = 1e9 + 7;
const int S = 1 << 20;
const int N = 20;
vector<int> adj[N];
ll dp[S][N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y; 
        cin >> x >> y;
        --x, --y;
        adj[y].pb(x);
    }
    dp[1][0] = 1;
    for (int i = 2; i < (1 << n); i++) {
        if ((!i & 1)) continue;
        if ((i & (1 << (n - 1))) &&
            (i != (1 << n) - 1)) {
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j))) continue;
            int prev = i - (1 << j);
            for (int k : adj[j]) {
                if (prev & (1 << k)) {
                    dp[i][j] += dp[prev][k];
                    dp[i][j] %= MOD;
                }
            }
        }
    }
    cout << dp[(1 << n) - 1][n - 1];
}
/**
 * TASK: Hamiltonian Flights.
 * ALGORITHM: Maintain the 
 * following DP states:
 * dp[S][V] = # of ways to do
 * the flights, if S is the subset
 * of cities visited, and V is the
 * current vertex.
 * 
 * DP state transition:
 * If a node K is adjacent to a node i,
 * then dp[S][i] += dp[B][K], where B
 * is every subset without node i.
*/