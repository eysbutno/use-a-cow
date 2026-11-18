#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 1;
set<int> adj[MAX];
vector<int> comps = {0};
set<int> unused;
void dfs(int node, int cmp) {
    comps[cmp]++;
    unused.erase(node);
    auto it = begin(unused);
    while (it != end(unused)) {
        if (adj[node].count((*it))) {
            ++it;
        } else {
            int next = *it;
            dfs(next, cmp);
            it = unused.lower_bound(next);
        }
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        unused.insert(i);
    }
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (unused.count(i)) {
            comps.push_back(0);
            dfs(i, ++cnt);
        }
    }
    sort(begin(comps), end(comps));
    cout << cnt << '\n';
    for (int i = 1; i <= cnt; i++) {
        cout << comps[i] << ' ';
    }
}
/*
Time Complexity: O(NlogN + M)
It's like the most
straightforward algorithm
you can think of, but with two
modifications to make it much faster.
A. Use a data structure like a set
to make searching for a node in
the adjacency list O(logN).
B. Instead of iterating through all the
possible nodes every time, only iterate
through the ones that have not been processed.
*/