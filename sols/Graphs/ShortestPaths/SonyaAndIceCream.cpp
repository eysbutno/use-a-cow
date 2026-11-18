#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 1e5 + 1;
const int INF = 1e9;
vector<pii> adj[MAX];
int n, k;
bool check(int mid) {
    vector<int> dist(n + 1);
    vector<int> deg(n + 1);
    vector<bool> active(n + 1, true);
    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        deg[i] = adj[i].size();
        if (deg[i] >= 3) ++cnt;
        if (deg[i] == 1) q.push(i);
    }
    int res = n;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        // can only traverse upwards;
        // only one real option
        pii edge;
        for (auto& i : adj[u]) {
            if (active[i.f]) {
                edge = i;
                break;
            }
        }
        if (dist[u] + edge.s > mid) {
            continue;
        }
        int p = edge.f, w = edge.s;
        ckmax(dist[p], dist[u] + w);
        active[u] = false;
        if (deg[p] == 3) --cnt;
        deg[p]--; --res;
        if (deg[p] == 1) {
            q.push(p);
        }
    }
    return (cnt == 0 && res <= k);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int x, y, w; 
        cin >> x >> y >> w;
        adj[x].pb({y, w});
        adj[y].pb({x, w});
    }
    int low = 0, high = n * 1e4;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (check(mid)) high = mid;
        else low = mid + 1;
    }
    cout << low << '\n';
}
/**
 * Binary search the distance.
 * From each leaf, find the max
 * distance from that leaf to another
 * leaf, until the distance > mid.
 * 
 * Implementation details:
 * To guarantee a path, all the nodes
 * with degree >= 3 initially must be reachable.
 * So, we run BFS. To correctly get the distance,
 * maintain a counter of how many edges have not
 * been used for each node. 
*/