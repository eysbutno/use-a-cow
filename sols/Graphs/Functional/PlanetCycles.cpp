#include <bits/stdc++.h>
using namespace std;

void dfs(int node, int cnt, vector<int>& res, 
    vector<bool>& vis, vector<vector<int>>& rev) {
    vis[node] = true;
    res[node] = cnt;
    for (int i : rev[node]) {
        dfs(i, cnt + 1, res, vis, rev);
    }
}
void floyd(int node, vector<vector<int>>& rev, 
    vector<bool>& vis, vector<int>& next, vector<int>& res) {
    int a = next[node], b = next[next[node]];
    while (a != b) {
        a = next[a];
        b = next[next[b]];
    }
    b = next[b];
    set<int> in = {a};
    while (a != b) {
        in.insert(b); 
        b = next[b];
    }
    int cnt = size(in);
    b = next[b];
    auto process = [&](int node) {
        res[node] = cnt; 
        vis[node] = 1;
        for (int i : rev[node]) {
            if (!in.count(i)) {
                dfs(i, cnt + 1, res, vis, rev);
            }
        }
    };
    process(a);
    while (a != b) {
        process(b);
        b = next[b];
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n; cin >> n;
    vector<int> next(n + 1), res(n + 1);
    vector<vector<int>> rev(n + 1);
    vector<bool> vis(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> next[i];
        rev[next[i]].push_back(i);
    }
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            floyd(i, rev, vis, next, res);
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << ' ';
    }
}
/*
For each connected component, find the cycle
and set all the distances for nodes in the cycle
to the size of the cycle. For each node, we check
if there are any nodes going into that node
that are NOT in the cycle. If so, we run DFS
to fill the distances from a node in the cycle.
*/