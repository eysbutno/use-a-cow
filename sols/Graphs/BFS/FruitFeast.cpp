#include <bits/stdc++.h>
using namespace std;
#define f first 
#define s second

int main() {
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
    int t, a, b; cin >> t >> a >> b;
    set<pair<int, bool>> vis; // fullness, drank water
    queue<pair<int, bool>> q;
    q.push({0, false});
    vis.insert({0, false});
    while (!q.empty()) {
        auto p = q.front();
        q.pop(); //vis.insert(p);
        if (!p.s) {
            pair<int, bool> state = {p.f / 2, true};
            if (!vis.count(state)) {
                vis.insert(state);
                q.push(state);
            }
        }
        for (int i : vector<int>{a, b}) {
            pair<int, bool> state = {p.f + i, p.s};
            if (p.f + i <= t && !vis.count(state)) {
                vis.insert(state);
                q.push(state);
            }
        }
    }
    int ans = -1;
    for (auto i : vis) {
        ans = max(i.f, ans);
    }
    cout << ans << "\n";
}
/*
Type: BFS
Time Complexity: O(t)
Algorithm:
Run BFS to create subtrees of possible decisions.
Use a set to store visited states. See the best
achieved state that was reached.
IMPORTANT NOTES:
You must store each state proactively, OTHERWISE 
many subtrees will be unnecessarily created.
An array COULD work, but would use too much memory
*/