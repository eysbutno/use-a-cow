#include <bits/stdc++.h>
using namespace std; 
using pii = pair<int, int>;
using ll = long long;
#define pb push_back
#define f first 
#define s second 

const int MAX = 4097;
int main() {
    int n; cin >> n;
    vector<vector<int>> trav(
        2, vector<int>(n));
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            cin >> trav[i][j];
        }
    }
    if (trav[0][1] != trav[1][1]) {
        cout << -1 << '\n';
        return 0;
    }
    vector<pii> ans;
    for (int i = 1; i < n; i++) {
        ans.push_back({1, trav[0][i]});
        if (i != n - 1) {
            ans.push_back({trav[1][i], trav[1][i + 1]});
        }
    }
    cout << size(ans) << '\n';
    for (auto& i : ans) {
        cout << i.f << ' ' << i.s << '\n';
    }
}
/*
Okay this problem can barely 
be considered a graph problem...
Add an edge between 1 and every
other node in the BFS traversal.
This will always satisfy the BFS
condition.
Add an edge between nodes i and
i + 1, if i is a node in the DFS
traversal.

Why doesn't this break the orderings?
- BFS traversal is obviously fullfilled.
- DFS traversal is fulfilled because any
  extra back edge that isn't needed will
  just get ignored by the DFS.
*/