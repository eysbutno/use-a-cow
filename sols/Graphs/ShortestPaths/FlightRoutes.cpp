#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int MAX = 100'001;
priority_queue<ll> best[MAX];
vector<pii> adj[MAX];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        int x, y, w; 
        cin >> x >> y >> w;
        adj[x].pb({y, w});
    }
    priority_queue<pll> q;
    best[1].push(0);
    q.push({0, 1});
    while (!q.empty()) {
        auto p = q.top(); q.pop();
        ll u = p.s, w = -p.f;
        if (w > best[u].top()) {
            continue;
        }
        for (auto& i : adj[u]) {
            ll t = i.s + w;
            if (best[i.f].size() < k) {
                best[i.f].push(t);
                q.push({-t, i.f});
            } else if (best[i.f].top() > t) {
                best[i.f].pop();
                best[i.f].push(t);
                q.push({-t, i.f});
            }
        }
    }
    vector<ll> res;
    while (size(best[n])) {
        res.pb(best[n].top());
        best[n].pop();
    }
    for (int i = k - 1; i >= 0; i--) {
        cout << res[i] << ' ';
    }
}
/**
 * Store each of the k best locations
 * in a priority queue.
 * 
 * When propogating from node to node,
 * only propogate the BEST time if
 * 1. The node has less than k paths.
 * 2. The worst time is worse than the current time.
*/