#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)
#define pb push_back
#define f first 
#define s second 

const int N = 2e5;
vector<pii> adj[N];
vector<vector<ll>> dp[N];
ll inDeg[N], l[N], w[N], rnk[N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        --x, --y;
        adj[y].pb({x, w});
        inDeg[x]++;
    }
    vector<int> q;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) q.pb(i);
    }
    while (!q.empty()) {
        vector<int> nxt;
        for (int i : q) {
            for (auto [v, d] : adj[i]) {
                --inDeg[v];
                dp[v].pb({-l[i], d, rnk[i], w[i] + d});
                if (!inDeg[v]) {
                    l[v] = l[i] + 1;
                    nxt.pb(v);
                }
            }
        }
        swap(nxt, q);
        vector<vector<ll>> opt;
        for (int i : q) {
            sort(all(dp[i]));
            w[i] = dp[i][0][3];
            opt.pb({dp[i][0][1], dp[i][0][2], i});
            dp[i].clear();
        }
        sort(all(opt));
        for (int i = 0; i < sz(opt); i++) {
            rnk[opt[i][2]] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cout << l[i] << ' ' << w[i] << '\n';
    }
}
/**
 * TASK: Minimum Longest Trip.
 * Observation 1: Graph is a DAG.
 * Observation 2: By reverse toposorting,
 * you can more effectively process the 
 * lexicographical orderings.
 * Algorithm: Reverse toposort. To process
 * the lexicographical ordering issue,
 * do the following:
 * 1. Batch process the paths to order them.
 * 2. For each path, store the relative order,
 * the weight of the edge taken, and the distance.
 * 3. To compare paths, compare the distances, then
 * compare the path weight, then compare the ranks.
*/