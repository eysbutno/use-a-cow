#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
#define ll long long

vector<ll> h, subtree_tot;
vector<vector<int>> adj;
vector<tuple<int, int, ll>> orders;
ll avg = 0;

void dfs_fill_subtrees(int node = 0, int par = 0) {
    subtree_tot[node] = h[node] - avg;
    for (int child : adj[node]) {
        if (child != par) {
            dfs_fill_subtrees(child, node);
            subtree_tot[node] += subtree_tot[child];
        }
    }
}
void dfs_make_orders(int node = 0, int par = 0) {
    for (int child : adj[node]) {
        if (child != par) {
            if (subtree_tot[child] >= 0) dfs_make_orders(child, node);
            if (subtree_tot[child] > 0) {
                orders.emplace_back(child, node, subtree_tot[child]);
            }
        }
    }
    for (int child : adj[node]) {
        if (child != par && subtree_tot[child] < 0) {
            orders.emplace_back(node, child, -subtree_tot[child]);
            dfs_make_orders(child, node);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    h.resize(n), adj.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> h[i]; avg += h[i];
    }
    avg /= n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v, --u, --v;
        adj[u].emplace_back(v), adj[v].emplace_back(u);
    }
    subtree_tot.resize(n);
    dfs_fill_subtrees();
    dfs_make_orders();
    cout << size(orders) << "\n";
    for (auto [u, v, b] : orders) cout << ++u << " " << ++v << " " << b << "\n";
}
/*
Type: DFS
Algorithm:
Get the average needed. After that, subtract the average
from each node and compute the subtree sums.
To compute all the orders, we recurse down the tree.
NOTE: The reason why we can solve everything in one iteration
of DFS is because we are recursing down the tree and having orders start at the bottom.
The recursive logic will only push_back the order for each subtree after all the orders
within that subtree are done.
*/