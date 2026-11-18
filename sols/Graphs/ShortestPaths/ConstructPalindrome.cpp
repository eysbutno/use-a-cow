#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second
const int MAX = 1e3 + 1;
const int INF = 1e9;
vector<int> adj[MAX][26];
int dist[MAX][MAX];
int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b; char c; 
        cin >> a >> b >> c;
        int v = c - 'a';
        adj[a][v].push_back(b);
        adj[b][v].push_back(a);
        edges[i] = {a, b};
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            dist[i][j] = INF;
        }
    }
    queue<pair<int, int>> q;
    q.push({1, n});
    dist[1][n] = 0;
    while (!q.empty()) {
        auto p = q.front(); q.pop();
        for (int l = 0; l < 26; l++) {
            for (int i : adj[p.f][l]) {
                for (int j : adj[p.s][l]) {
                    if (dist[p.f][p.s] + 1
                        < dist[i][j]) {
                        dist[i][j] = dist[p.f][p.s] + 1;
                        q.push({i, j});
                    }
                }
            }
        }
    }
    int ans = INF;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dist[i][i] * 2);
    }
    for (auto& i : edges) {
        int best = 2 * min(dist[i.f][i.s],
            dist[i.s][i.f]) + 1;
        ans = min(ans, best);
    }
    if (ans != INF) cout << ans << '\n';
    else cout << -1 << '\n';
}
/*
lowk disappointed for not
getting this one....

Keep a pair of integers
that will keep track the
two nodes the path is at.
Basically, keep symmetry
and floodfill all the 
possible pairs of locations
you can have. Do some math
and get answer. Kaboom.
*/