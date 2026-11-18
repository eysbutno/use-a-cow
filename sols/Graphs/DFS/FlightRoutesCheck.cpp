#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj1;
vector<vector<int>> adj2;
vector<bool> visited1;
vector<bool> visited2;
void dfs1(int node) {
    visited1[node] = 1;
    for (int i : adj1[node]) {
        if (!visited1[i]) dfs1(i);
    }
}
void dfs2(int node) {
    visited2[node] = 1;
    for (int i : adj2[node]) {
        if (!visited2[i]) dfs2(i);
    }
}
int main() {
    int n, m; cin >> n >> m;
    adj1.resize(n + 1); adj2.resize(n + 1);
    visited1.resize(n + 1); visited2.resize(n + 1);
    for (int i = 0; i < m; i++) {
        int l1, l2; cin >> l1 >> l2;
        adj1[l1].push_back(l2);
        adj2[l2].push_back(l1);
    }
    dfs1(1);
    for (int i = 2; i <= n; i++) {
        if (!visited1[i]) {
            cout << "NO" << "\n" << 1 << " " << i;
            return 0;
        }
    }
    dfs2(1);
    for (int i = 2; i <= n; i++) {
        if (!visited2[i]) {
            cout << "NO" << "\n" << i << " " << 1;
            return 0;
        }
    }
    cout << "YES" << "\n";
    return 0;
}
/*
Type: DFS
Algorithm:
DFS 1 is to connect all the nodes in terms of if you can fly there
DFS 2 is to connect all the nodes in terms of if it can be flown to
*/