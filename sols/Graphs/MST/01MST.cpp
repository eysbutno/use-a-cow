#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second 

struct DSU {
    vector<int> e;
    DSU(int n) { 
        e = vector<int>(n, -1); 
    }
    int get(int x) { 
        return e[x] < 0 ? x : e[x] = get(e[x]); 
    }
    bool connected(int a, int b) {
        return get(a) == get(b); 
    }
    int size(int x) { 
        return -e[get(x)]; 
    }
    bool unite(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return false;
        if (e[x] > e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
ll sum(int val) {
    return ((ll) val * (val - 1)) / 2;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);
    int n, m; cin >> n >> m;
    vector<set<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    set<int> unused;
    for (int i = 1; i <= n; i++) {
        unused.insert(i);
    }
    DSU dsu(n + 1);
    auto comp = [&](int node) {
        queue<int> q;
        q.push(node);
        while (!q.empty()) {
            int p = q.front(); q.pop();
            auto it = begin(unused);
            while (it != end(unused)) {
                if (adj[p].count(*it)) {
                    ++it;
                } else {
                    dsu.unite(p, *it);
                    int temp = *it;
                    unused.erase(it);
                    it = unused.lower_bound(temp);
                    q.push(temp);
                }
            }
        }
    };
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (dsu.size(i) == 1) {
            comp(i); ++res;
        }
    }
    cout << res - 1 << '\n';
}
/*
Basically the
Connected Components? 
CF question, but a bit
different. All you need
to do is find the connected
components for the 0 cost
edges, and realize you 
just need comp_num - 1
1 cost edges to connect
the whole thing.
*/