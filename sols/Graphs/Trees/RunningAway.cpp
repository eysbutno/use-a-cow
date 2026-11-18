#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define f first 
#define s second 

template<class T> bool smin(T& a, T b) {
    return b < a ? a = b, 1 : 0;
}
template<class T> bool smax(T& a, T b) {
    return b > a ? a = b, 1 : 0;
}
void solve() {
    ll n, l; cin >> n >> l;
    vector adj(n, vector<array<ll, 2>>());
    for (int i = 1; i < n; i++) {
        ll p, d; cin >> p >> d;
        adj[--p].push_back({i, d});
    }
    vector<int> res(n);
    vector<priority_queue<ll>> cur(n);
    auto merge = [&](int i, int j, ll dx) -> void {
        // merges nodes i and j's priority queues.
        if (sz(cur[i]) < sz(cur[j])) {
            cur[i].swap(cur[j]);
        }
        while (!cur[j].empty()) {
            cur[i].push(cur[j].top());
            cur[j].pop();
        }
        while (!cur[i].empty() && cur[i].top() - dx > l) {
            cur[i].pop();
        }
    };
    auto dfs = [&](int u, ll dep, auto&& dfs) -> void {
        for (auto [v, w] : adj[u]) {
            dfs(v, dep + w, dfs);
            merge(u, v, dep);
        }
        cur[u].push(dep);
        res[u] = sz(cur[u]);
    }; dfs(0, 0, dfs);
    for (int i = 0; i < n; i++) {
        cout << res[i] << "\n";
    }
}
int main() {
    cin.tie(0) -> sync_with_stdio(0);
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
    int t = 1; // cin >> t;
    while (t--) solve();
}
/**
 * TASK: Running From The Barn (USACO)
 * At every node, maintain a priority queue of
 * the distances from the root of every subtree
 * node. Then, pop all the nodes that are too
 * far down. 
*/