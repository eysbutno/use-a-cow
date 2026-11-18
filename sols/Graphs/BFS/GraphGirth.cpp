#include <bits/stdc++.h>
using namespace std;

const int MAX = 2501;
vector<int> adj[MAX];
int solve(int n, int s) {
    vector<int> dist(n + 1, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    int ans = INT_MAX;
    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (int i : adj[p]) {
            if (dist[i] == -1) {
                dist[i] = dist[p] + 1;
                q.push(i);
            } else if (dist[i] >= dist[p]) {
                ans = min(ans, dist[i] 
                    + dist[p] + 1);
            }
        }
    }
    return ans;
}
int main() {
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = INT_MAX;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, solve(n, i));
    }
    cout << ((ans != INT_MAX) ? ans : -1) << '\n';
}
/*
Brute force nodes that start the optimal
cycle. To find the minimal cycle, you
recalculate a possible answer each time
a node runs into another node (that cannot
be itself, which is why the dist >= cur dist).
*/