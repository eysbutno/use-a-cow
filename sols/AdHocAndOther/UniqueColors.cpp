#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int MAX = 2e5 + 1;
vector<int> adj[MAX];
set<int> group[MAX];
int res[MAX];
void merge(int x, int y) {
    // y goes into x
    if (size(group[x]) < size(group[y])) {
        swap(group[x], group[y]);
    }
    for (int i : group[y]) {
        group[x].ins(i);
    }
    group[y].clear();
    // freeing up memory
}
void dfs(int node, int prev) {
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node);
            merge(node, i);
        }
    }
    res[node] = size(group[node]);
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i <= n; i++) {
        int c; cin >> c;
        group[i].ins(c);
    }
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}