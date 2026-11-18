#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define pb push_back
#define f first 
#define s second 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);
    int m, n, l; cin >> m >> n >> l;
    vector<vector<pii>> reg(m + 1);
    vector<set<int>> part(n + 1);
    map<pii, vector<int>> comps;
    vector<int> locs(l);
    for (int& i : locs) cin >> i;
    for (int i = 1; i <= m; i++) {
        int sz; cin >> sz;
        vector<int> temp(sz);
        for (int j = 0; j < sz; j++) {
            cin >> temp[j];
            part[temp[j]].insert(i);
        }
        for (int j = 1; j < sz; j++) {
            pii a = {temp[j - 1], temp[j]};
            if (a.f > a.s) swap(a.f, a.s);
            reg[i].pb(a);
            comps[a].pb(i);
        }
        pii a = {temp[0], temp[sz - 1]};
        if (a.f > a.s) swap(a.f, a.s);
        reg[i].pb(a);
        comps[a].pb(i);
    }
    vector<set<int>> adj(m + 1);
    for (int i = 1; i <= m; i++) {
        for (auto& j : reg[i]) {
            for (int k : comps[j]) {
                adj[i].insert(k);
            }
        }
    }
    vector<int> sum(m + 1);
    auto process = [&](int node) {
        vector<int> dist(m + 1, 2e9);
        queue<int> q;
        for (int i : part[node]) {
            dist[i] = 0;
            q.push(i);
        }
        while (size(q)) {
            int p = q.front(); q.pop();
            for (int i : adj[p]) {
                if (dist[p] + 1 < dist[i]) {
                    dist[i] = dist[p] + 1;
                    q.push(i);
                }
            }
        }
        for (int i = 1; i <= m; i++) {
            sum[i] += dist[i];
        }
    };
    for (int i = 0; i < l; i++) {
        process(locs[i]);
    }
    auto test = [&]() {
        for (int i = 1; i <= n; i++) {
            cout << i << ": ";
            for (int j : part[i]) 
                cout << j << ' ';
            cout << '\n';
        }
        for (int i = 1; i < m; i++) {
            cout << sum[i] << ' ';
        }
        cout << '\n';
    };
    // test();
    int best = 2e9, res = -1;
    for (int i = 1; i <= m; i++) {
        if (sum[i] < best) {
            best = sum[i];
            res = i;
        }
    }
    cout << best << '\n';
    cout << res << '\n';
}
/*
Problem Checklist:
1. What are some possible time
complexities?
2. (Make some observations)
3. Are there any subproblems
that break said problem into
smaller, more workable pieces?
4. (Run through possible ideas:
graph, bisearch, sortings?)
5. If it's a game theory/problem
where there's "choices", are there
any "invariants"?

Observations:
1. A node can automatically access all
the regions its a part of.
2. A node can access all the regions
with a common border by crossing one 
great wall.

Algorithm Idea:
Run BFS on each of the nodes
you start at. Sum the distances.
The graph's construction is detailed
above.
*/