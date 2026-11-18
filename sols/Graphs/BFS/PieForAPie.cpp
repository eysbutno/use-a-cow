#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
#define pb push_back
#define f first 
#define s second 

const int INF = 2e9;
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("piepie.in", "r", stdin);
    freopen("piepie.out", "w", stdout);
    int n, d; cin >> n >> d;
    vector<pii> bes(n), els(n);
    multiset<pii> b, e;
    queue<int> q; // for BFS later
    vector<int> dist(n * 2, 2e9);
    for (int i = 0; i < n; i++) {
        cin >> bes[i].f >> bes[i].s;
        b.insert({bes[i].f, i});
        if (!bes[i].s) {
            q.push(i);
            dist[i] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> els[i].f >> els[i].s;
        e.insert({els[i].f, n + i});
        if (!els[i].f) {
            q.push(n + i);
            dist[n + i] = 0;
        }
    }
    vector<vector<int>> adj(n * 2);
    auto build = [&](multiset<pii>& a,
        multiset<pii>& b) {
        for (auto& i : a) {
            auto it = b.lower_bound({i.f, -1});
            while (it != end(b)) {
                auto p = *it;
                if (p.f > i.f + d) {
                    break;
                }
                adj[p.s].pb(i.s);
                ++it;
            }
        }
    };
    build(e, b);
    b.clear(); e.clear();
    for (int i = 0; i < n; i++) {
        b.insert({bes[i].s, i});
        e.insert({els[i].s, n + i});
    }
    build(b, e);
    while (!q.empty()) {
        int p = q.front(); q.pop();
        for (int i : adj[p]) {
            if (dist[p] + 1 < dist[i]) {
                dist[i] = dist[p] + 1;
                q.push(i);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << (dist[i] != INF ? 
            dist[i] + 1 : -1) << '\n';
    }
}