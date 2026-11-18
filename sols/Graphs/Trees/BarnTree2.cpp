#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define f first 
#define s second 

ll dfs(int node, int prev, int& num, vector<vector<ll>>& adj,
    vector<vector<pair<ll, ll>>>& orders, vector<int>& vals) {
    ll tot = vals[node];
    for (int i : adj[node]) {
        if (i != prev) {
            ll res = dfs(i, node, num, adj, orders, vals);
            if (res > 0) {
                orders[i].push_back({node, res});
            } else if (res < 0) {
                orders[node].push_back({i, -res});
            }
            tot += res, num += (res != 0);
        }
    }
    return tot;
}
void print(int node, vector<bool>& vis,
    vector<vector<pair<ll, ll>>>& orders1,
    vector<vector<pair<ll, ll>>>& orders2) {
    vis[node] = 1;
    for (auto i : orders2[node]) {
        if (!vis[i.f]) print(i.f, vis, orders1, orders2);
    }
    for (auto i : orders1[node]) {
        cout << node << ' ' << i.f << ' ' << i.s << '\n';
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    ll sum = 0;
    vector<int> vals(n + 1), cnt(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> vals[i]; sum += vals[i];
    }
    sum /= n;
    for (int& i : vals) {
        i -= sum;
    }
    vector<vector<pair<ll, ll>>> orders1(n + 1);
    vector<vector<ll>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int x, y; cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    int ans = 0;
    dfs(1, -1, ans, adj, orders1, vals);
    cout << ans << '\n';
    vector<bool> vis(n + 1);
    vector<vector<pair<ll, ll>>> orders2(n + 1);
    for (int i = 0; i < size(orders1); i++) {
        for (auto j : orders1[i]) {
            orders2[j.f].push_back({i, j.s});
        }
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) print(i, vis, orders1, orders2);
    }
}
/*
Algorithm:
First, compute all the required orders (the method should be
obvious). Next, to find a valid ordering, you'll need to
essentially construct a directed graph of routes. There
will always be a node that has an outbound edge but no
inbound edge. You want to start with that to guarantee 
all barns will have enough haybales. To do this,
you want to recurse up the tree and then print out all the orders.
*/