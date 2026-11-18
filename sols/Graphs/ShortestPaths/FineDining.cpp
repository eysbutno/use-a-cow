#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using pdi = pair<double, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

const int MAX = 5e4 + 1, 
    INF = 1000000000;
int dp[2][MAX], tasty[MAX];
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    freopen("dining.in", "r", stdin);
    freopen("dining.out", "w", stdout);
    int n, m, k; 
    cin >> n >> m >> k;
    vector<vector<pii>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b, t; 
        cin >> a >> b >> t;
        adj[a].pb({b, t});
        adj[b].pb({a, t});
    }
    for (int i = 0; i < k; i++) {
        int idx, val; 
        cin >> idx >> val;
        tasty[idx] = val;
    }
    for (int i = 0; i < n; i++) {
        dp[0][i] = INF;
        dp[1][i] = INF;
    }
    dp[0][n] = 0;
    // do some "dp" here lmao
    priority_queue<pair<int, pii>> pq;
    pq.push({0, {n, 0}});
    while (size(pq)) {
        auto p = pq.top(); pq.pop();
        int t = -p.f, u = p.s.f, s = p.s.s;
        if (dp[s][u] != t) continue;
        for (pii& i : adj[u]) {
            if (dp[s][u] + i.s < dp[s][i.f]) {
                dp[s][i.f] = dp[s][u] + i.s;
                pq.push({-dp[s][i.f], {i.f, s}});
            }
        }
        if (!s && tasty[u] && dp[1][u] > 
            dp[0][u] - tasty[u]) {
            dp[1][u] = dp[0][u] - tasty[u];
            pq.push({-dp[1][u], {u, 1}});
        }
    }
    for (int i = 1; i < n; i++) {
        if (dp[1][i] <= dp[0][i]) {
            cout << 1 << '\n';
        } else {
            cout << 0 << '\n';
        }
    }
}   
/*
Observation 1:
You just need to run
Dijkstra's / other SP
from node N
Observation 2:
You can use DP/a state 
transition. Basically,
if there's a haybale
at your current location,
start another state at
the current haybale except
you ate one.

Impl details:
Subtracts haybale yumminess
in order to simplify implementation.

NOTE: the correct way
to implement the state transition
is to push to the priority queue.
Whatever I did previously absolutely
does not work.
*/