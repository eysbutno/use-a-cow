#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int MAX = 1e5 + 1;
vector<int> adj[MAX];
int bef[MAX], dist, n;
int dfs(int node, int prev, int dx) {
    if (node == n) dist = dx;
    int res = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            res += dfs(i, node, dx + 1);
            bef[i] = node;
        }
    }
    return res;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int tot = dfs(1, -1, 0);
    if (dist % 2) {
        dist /= 2;
    } else {
        dist /= 2;
        --dist;
    }
    int meet = n;
    while (dist--) {
        meet = bef[meet];
    }
    int sub = dfs(meet, bef[meet], 0);
    if (tot > sub * 2) {
        cout << "Fennec";
    } else {
        cout << "Snuke";
    }
    cout << '\n';
}
/**
 * So Fennec and Snuke both want 
 * to go towards each other; which ever
 * player gets more points as a result will
 * win.
*/