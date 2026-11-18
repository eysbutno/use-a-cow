#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 2e5;
vector<int> adj[N], dep[N];
int st[N], ed[N], t;
void tour(int node, int dx) {
    st[node] = t++;
    dep[dx].pb(t - 1);
    for (int i : adj[node]) {
        tour(i, dx + 1);
    }
    ed[node] = t;
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int p; cin >> p;
        adj[--p].pb(i);
    }
    tour(0, 0);
    auto query = [&](int u, int d) {
        return (lower_bound(all(dep[d]), ed[u]) - 
                lower_bound(all(dep[d]), st[u]));
    };
    int q; cin >> q;
    while (q--) {
        int u, d; cin >> u >> d;
        cout << query(--u, d) << '\n';
    }
}
/**
 * TASK: Count Descendants.
 * Observation 1: All nodes in question will
 * have a depth of d_i.
 * 
 * Observation 2: All nodes in question are contained
 * in node u_i's subtree.
 * 
 * Based on this information, we only need to keep track
 * of the nodes visited within u_i's subtree. This is easily
 * done with Euler Tour and lower_bound.
*/