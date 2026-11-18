#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define smax(a, b) a = max(a, b)
#define smin(a, b) a = min(a, b)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5 + 1;
vector<int> adj[N];
int pos[N], res;
void dfs(int node, int prev) {
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            if (pos[i] == i) {
                swap(pos[i], pos[node]);
                res += 2;
            }
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int i = 1; i <= n; i++) {
        pos[i] = i;
    }
    dfs(1, 0);
    if (pos[1] == 1) {
        swap(pos[1], pos[adj[1][0]]);
        res += 2;
    }
    cout << res << '\n';
    for (int i = 1; i <= n; i++) {
        cout << pos[i] << ' ';
    }
}
/**
 * IDK why this is in the DP section,
 * as just greedying it makes more sense.
*/