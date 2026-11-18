#include <bits/stdc++.h>
using namespace std;
#define ll long long 

const int MAX = 2e5 + 1;
vector<int> adj[MAX];
ll desc[MAX], dists[MAX];
int dfs1(int node, int prev) {
    int cnt = 1;
    for (int i : adj[node]) {
        if (i != prev) {
            cnt += dfs1(i, node);
            dists[node] += dists[i];
        }
    }
    desc[node] = cnt;
    dists[node] += cnt - 1;
    return cnt;
}
void dfs2(int node, int prev) {
    for (int i : adj[node]) {
        if (i != prev) {
            dists[i] = dists[node] + 
                desc[1] - 2 * desc[i];
            dfs2(i, node);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    for (int i = 1; i < n; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, -1); dfs2(1, -1);
    for (int i = 1; i <= n; i++) {
        cout << dists[i] << ' ';
    }
}
/*
First, do some precalculation.
Calculate the sum of the distances
from each subtree, and the # of
nodes in each subtree.

Next, for getting the final answer
for each node, each node's sum
of distances is expressed by
it's parent's sum + n - 2 *
# of nodes in the subtree.

Math Explanation: 
dists[node]: kind of obvious
desc[1]: used later to get
# of nodes in tree that
are not in our particular subtree.
subtracting desc[1] again: previously,
dist[node]'s distances is made with
the consideration that each node is
1 node further than it now is.
*/