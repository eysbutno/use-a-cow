#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define smin(a, b) a = min(a, b)
#define smax(a, b) a = max(a, b)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 1e5;
vector<int> adj[N];
int pathLen[N];
bool dfs(int u, int p, int k) {
    map<int, int> mp;
    for (int i : adj[u]) {
        if (i != p) {
            if (!dfs(i, u, k)) {
                return false;
            }
            int cur = pathLen[i] + 1;
            if (cur != k) mp[cur]++;
        }
    }
    for (auto [v, w] : mp) {
        if (k - v == v) {
            if (w % 2) {
                if (pathLen[u]) {
                    return false;
                } else {
                    pathLen[u] = v;
                }
            }
        } else {
            if (w > mp[k - v]) {
                if (w - mp[k - v] > 1
                    || pathLen[u]) {
                    return false;
                } else {
                    pathLen[u] = v;
                }
            }
        }
    }
    return true;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("deleg.in", "r", stdin);
    freopen("deleg.out", "w", stdout);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        --x, --y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int k = 1; k < n; k++) {
        if ((n - 1) % k) {
            cout << 0;
        } else {
            fill(pathLen, pathLen + n, 0);
            cout << (dfs(0, -1, k) && !pathLen[0]);
        }
    }
}
/**
 * Observation 1:
 * If (n - 1) % k != 0, the 
 * answer cannot be 1.
 * 
 * Observation 2:
 * Each leaf must be merged 
 * upwards, on and on.
 * 
 * Algorithm:
 * Build upwards, and merge paths.
 * Boom.
 * 
 * NOTE: Only check the divisors.
 * Because apparently there are
 * around log(N) divisors for any
 * random number N. 
*/