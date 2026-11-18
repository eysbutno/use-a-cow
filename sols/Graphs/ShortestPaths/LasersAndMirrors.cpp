#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second 

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    freopen("lasers.in", "r", stdin);
    freopen("lasers.out", "w", stdout);
    int n; cin >> n;
    vector<pair<int, int>> locs(n + 2);
    cin >> locs[0].f >> locs[0].s;
    cin >> locs[n + 1].f >> locs[n + 1].s;
    for (int i = 1; i <= n; i++) {
        cin >> locs[i].f >> locs[i].s;
    }
    unordered_map<int, vector<int>> px, py;
    for (int i = 0; i <= n + 1; i++) {
        px[locs[i].f].push_back(i);
        py[locs[i].s].push_back(i);
    }
    vector<int> dists(n + 2, -1);
    queue<int> q;
    unordered_map<int, bool> sx, sy;
    q.push(0);
    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (int i : px[locs[p].f]) {
            if (sx[locs[p].f]) break;
            if (dists[i] == -1) {
                dists[i] = dists[p] + 1;
                q.push(i);
            }
        }
        for (int i : py[locs[p].s]) {
            if (sy[locs[p].s]) break;
            if (dists[i] == -1) {
                dists[i] = dists[p] + 1;
                q.push(i);
            }
        }
        sx[locs[p].f] = 1;
        sy[locs[p].s] = 1;
    }
    cout << ((dists[n + 1] > 0) ? dists[n + 1] - 1 : -1);
}
/*
Shortest path between the start and end, 
using BFS. 

The optimal solution will never
need to worry about mirrors
intersecting for obvious reasons.
*/