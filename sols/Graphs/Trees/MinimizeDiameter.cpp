#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

int res, dis = -1;
const int MAX = 2e5 + 1;
vector<int> adj[MAX];
void dfs(int node, int prev, 
    int d, int id) {
    if (d > dis) {
        dis = d, res = node;
    }
    for (int i : adj[node]) {
        if (i != prev) {
            dfs(i, node, d + 1, id);
        }
    }
}
int sol(int n) {
    dis = 0;
    dfs(1, -1, 0, 0);
    dis = 0;
    dfs(res, -1, 0, 0);
    dfs(res, -1, 0, 1);
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
    }
    return dis;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int x, y; 
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int d1 = sol(n);
    int m; cin >> m;
    for (int i = 1; i < m; i++) {
        int x, y;
        cin >> x >> y;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    int d2 = sol(m);
    int r1 = ((d1 + 1) / 2) + 
        ((d2 + 1) / 2) + 1;
    cout << max(max(d1, d2), r1);
}
/*
This problem is kind of wack.
Original solution gets WA. I 
don't know why, but it does.

Solution:
Calculate the diameter for both
trees. 

The solution is as follows:
Max of two options:
A. ceil(d1 / 2) + ceil(d2 / 2) + 1.
Basically, this is saying that its
optimal to have the new diameter be 
half of the optimal diameters plus one
for the new edge.

B. Max of diameter 1 and diameter 2.
This is usually optimal if one diameter
is super long, and the other one is 
super short. In that case, the diameter is
the max of d1 and d2.
*/