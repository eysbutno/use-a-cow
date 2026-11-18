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

const int N = 2e5;
vector<int> adj[N];
vector<int> topsort;
int inDeg[N];
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        inDeg[y]++;
        adj[x].pb(y);
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) pq.push(-i);
    }
    while (!pq.empty()) {
        int u = -pq.top(); pq.pop();
        topsort.pb(u);
        for (int i : adj[u]) {
            --inDeg[i];
            if (!inDeg[i]) {
                pq.push(-i);
            }
        }
    }
    if (sz(topsort) != n) {
        cout << "IMPOSSIBLE" << '\n';
        return 0;
    }
    for (int i : topsort) {
        cout << i + 1 << ' ';
    }
    cout << '\n';
}
/**
 * Lexicographically minimum
 * toposort, using Kahns.
*/