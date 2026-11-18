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
        ++inDeg[x];
        adj[y].pb(x);
    }
    priority_queue<int> pq;
    for (int i = 0; i < n; i++) {
        if (!inDeg[i]) pq.push(i);
    }
    while (!pq.empty()) {
        int u = pq.top(); pq.pop();
        topsort.pb(u);
        for (int i : adj[u]) {
            --inDeg[i];
            if (!inDeg[i]) {
                pq.push(i);
            }
        }
    }
    while (sz(topsort)) {
        cout << topsort.back() + 1 << ' ';
        topsort.pop_back();
    }
    cout << '\n';
}
/**
 * Toposort on the reverse graph,
 * to create the maximum lexicographical
 * sort. This, in turn, will always place
 * the smaller elements as far back as possible.
 * Then we just reverse the toposort.
*/