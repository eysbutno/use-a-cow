#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
#define ckmin(a, b) a = min(a, b)
#define ckmax(a, b) a = max(a, b)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define pb push_back 
#define ins insert
#define f first 
#define s second

const int N = 1e5 + 1;
vector<int> adj[N];
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
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    int n, m; cin >> n >> m;
    set<pii> active;
    vector<int> deg(n + 1);
    for (int i = 0; i < m; i++) {
        int x, y; cin >> x >> y;
        deg[x]++, deg[y]++;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int i = 1; i <= n; i++) {
        active.ins({sz(adj[i]), i});
    }
    vector<int> minDeg(n), rem(n);
    vector<bool> inComp(n + 1, true);
    for (int i = 0; i < n; i++) {
        auto it = begin(active);
        pii cow = *it;
        active.erase(it);
        minDeg[i] = cow.f;
        rem[i] = cow.s;
        inComp[cow.s] = false;
        for (int j : adj[cow.s]) {
            if (inComp[j]) {
                active.erase({deg[j], j});
                deg[j]--;
                active.ins({deg[j], j});
            }
        }
    }
    reverse(all(minDeg));
    reverse(all(rem));
    ll res = 0;
    int mx = 1;
    DSU dsu(n + 1);
    for (int i = 0; i < n; i++) {
        int u = rem[i];
        for (int j : adj[u]) {
            if (inComp[j]) {
                dsu.unite(u, j);
            }
        }
        inComp[u] = true;
        ckmax(mx, dsu.size(u));
        ckmax(res, 1LL * minDeg[i] * mx);
    }
    cout << res << '\n';
}
/**
 * For each component, you keep on
 * removing the cow with the least 
 * friendships.
 * 
 * To compute the result, simulate adding
 * the edges in to calculate the largest 
 * connected component. Note that we only 
 * care about the largest component at some
 * given time and the minimum degree. The
 * reason is that if there is a connected
 * component that has a better minimum
 * friendship value, it'll eventually be reached
 * by the node removal.
*/