#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second

int main() {
    cin.tie(0) -> sync_with_stdio(false);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> edges(m);
    for (auto& i : edges) cin >> i.f >> i.s;
    vector<set<int>> path(n + 1);
    vector<int> ord(n + 1);
    for (int i = 1; i <= n; i++) ord[i] = i;
    for (auto& i : edges) {
        path[ord[i.f]].insert(i.s);
        path[ord[i.s]].insert(i.f);
        swap(ord[i.f], ord[i.s]);
    }
    vector<bool> vis(n + 1);
    vector<int> res(n + 1, 1);
    auto process = [&](int node) {
        vector<int> cycle = {node};
        int a = node, b = ord[a];
        while (a != b) {
            cycle.push_back(b);
            b = ord[b];
        }
        set<int> seen;
        for (int i : cycle) {
            for (int j : path[i]) {
                seen.insert(j);
            }
        }
        b = ord[a];
        vis[a] = 1;
        while (a != b) {
            res[b] = size(seen);
            vis[b] = 1;
            b = ord[b];
        }
        res[a] = size(seen);
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) process(i);
    }
    for (int i = 1; i <= n; i++) {
        if (res[i]) cout << res[i] << '\n';
        else cout << 1 << '\n';
    }
}
/*
This is essentially a functional graph problem.
To interpret it as a functional graph, you just have
the next node be whereever a cow goes after K mooves.
*/