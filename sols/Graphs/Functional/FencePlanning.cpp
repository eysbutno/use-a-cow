#include <bits/stdc++.h>
using namespace std;
#define INF 2000000000
vector<vector<int>> adj, net; 
vector<pair<int, int>> loc;
vector<bool> visited; 
void dfs(int node, int network) {
    visited[node] = true;
    for (int i : adj[node]) {
        if (!visited[i]) {
            net[network].push_back(i);
            dfs(i, network);
        }
    }
}
int main() {
    ifstream fin ("fenceplan.in");
    ofstream fout ("fenceplan.out");
    int n, m; fin >> n >> m;
    loc.resize(n + 1); 
    adj.resize(n + 1);
    visited.resize(n + 1);
    net.resize(n);
    for (int i = 1; i <= n; i++) {
        fin >> loc[i].first >> loc[i].second;
    }
    for (int i = 0; i < m; i++) {
        int a, b; fin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int num = -1;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            num++; dfs(i, num);
            net[num].push_back(i);
        }
    }
    int ans = INF;
    for (int i = 0; i <= num; i++) {
        int left = INF, right = -1, top = -1, bot = INF;
        for (int j : net[i]) {
            int x = loc[j].first, y = loc[j].second;
            left = min(x, left); right = max(x, right);
            bot = min(y, bot); top = max(y, top);
        }
        ans = min(ans, 2 * (right - left + top - bot));
    }
    fout << ans << endl;
    return 0;
}