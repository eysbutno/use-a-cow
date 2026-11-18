#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
int dfs(int node, int prev) {
    int ans = 0, cows = adj[node].size();
    cows += (int) prev == -1;
    int cur = 1, days = 0;
    while (cur < cows) {
        days++, cur *= 2;
    }
    ans += days;
    for (int i : adj[node]) {
        if (i != prev) ans += dfs(i, node) + 1;
    }
    return ans;
}
int main() {
    int n; cin >> n;
    adj.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << dfs(0, -1) << "\n";;
}
/*
Type: DFS (Tree)
Algorithm:
At each node, replicate enough for each child node
Repeat until you get your final answer
(The reason cur < cows is the correct loop condition is 
because we include the parent node in the adjacency list)
*/