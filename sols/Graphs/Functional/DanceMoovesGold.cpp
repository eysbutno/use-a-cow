#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back
#define ins insert
#define f first 
#define s second 

const int N = 1e5 + 1;
vector<pii> s[N];
int p[N], f[N], res[N], 
    frq[N], uniq;
bool vis[N];
void add(int u, int mx) {
    for (auto [k, v] : s[u]) {
        if (v > mx) break;
        if (!frq[k]) ++uniq;
        ++frq[k];
    }
}
void del(int u, int mx) {
    for (auto [k, v] : s[u]) {
        if (v > mx) break;
        if (frq[k] == 1) --uniq;
        --frq[k];
    }
}
void dfs(int u, vector<int>& cycle) {
    if (vis[u]) return;
    vis[u] = true;
    cycle.pb(u);
    dfs(f[u], cycle);
}
int main() {
	cin.tie(0) -> sync_with_stdio(0);
    int n, k; ll m; cin >> n >> k >> m;
    for (int i = 1; i <= n; i++) {
        p[i] = i, s[i].pb({i, 0});
    }
    for (int i = 1; i <= k; i++) {
        int x, y; cin >> x >> y;
        s[p[x]].pb({y, i});
        s[p[y]].pb({x, i});
        swap(p[x], p[y]);
    }
    for (int i = 1; i <= n; i++) {
        f[p[i]] = i;
    }
    auto process = [&](int node) {
        ll it = m / k, rem = m % k;
        vector<int> cycle;
        dfs(node, cycle);
        int z = sz(cycle);
        if (it >= z) {
            it = z, rem = 0;
        }
        int edp = it - 1;
        for (int i = 0; i <= edp; i++) {
            add(cycle[i], k);
        }
        for (int i = 0; i < z; i++) {
            int nw = (edp + 1) % z;
            add(cycle[nw], rem);
            res[cycle[i]] = uniq;
            del(cycle[nw], rem);
            del(cycle[i], k);
            add(cycle[nw], k);
            edp = nw;
        }
        for (int i = 0; i < it; i++) {
            del(cycle[i], k);
        }
    };
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) process(i);
    }
    for (int i = 1; i <= n; i++) {
        cout << res[i] << '\n';
    }
}
/**
 * TASK: Dance Mooves.
 * Construct a graph, where there's an edge
 * between a and b if after k swaps a goes
 * to position b.
 * 
 * Then, use sliding window to solve the problem.
*/