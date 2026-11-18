#include <bits/stdc++.h>
using namespace std;
// tree problem
vector<vector<int>> adj; 
vector<int> color;
string type; int c = 0;
void dfs(int node) {
    color[node] = c;
    for (int i : adj[node]) {
        if (!color[i] && type[node] 
            == type[i]) {
            dfs(i);
        }
    }
}
void setIO(string name = "") {
    ios_base::sync_with_stdio(0); cin.tie(0);
    if (name.size()) {
       freopen((name + ".in").c_str(), "r", stdin);
       freopen((name + ".out").c_str(), "w", stdout);
    }
}
int main() {
    setIO("milkvisits");
    int n, m; cin >> n >> m >> type;
    adj.resize(n), color.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (!color[i]) {c++; dfs(i);}
    }
    for (int i = 0; i < m; i++) {
        int a, b; char p; cin >> a >> b >> p; a--, b--;
        cout << (type[a] == p || color[a] != color[b]);
    }
}