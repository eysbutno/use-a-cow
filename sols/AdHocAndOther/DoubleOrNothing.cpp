#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int MAX = 1e5 + 1;
vector<int> adj[MAX];
void solve() {
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int cnt = 0;
    set<int> ignore;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() <= 1) {
            ignore.ins(i);
        }
    }
    for (int i = 1; i <= n; i++) {
        int temp = 0;
        for (int j : adj[i]) {
            if (!ignore.count(j)) {
                ++temp;
            }
        }
        if (temp <= 1 && !ignore.count(i)) {
            ++cnt;
        }
    }
    if (cnt <= 2 && n > 2) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    cout << '\n';
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int t; cin >> t;
    while (t--) {
        solve();
    }
}
/**
 * Observations:
 * 1. Graph is a tree.
 * 2. Adding an edge creates a cycle.
 * 3. Ideal graph should have big cycle
 *    with some nodes directly attached.
 * 
 * Remove all the leaf nodes in the graph,
 * and count how many leaf nodes are left.
 * If that count <= 2, and n > 2, you can
 * do it.
*/